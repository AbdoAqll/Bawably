#include "TenantController.h"
#include <iostream>
#include "Application/UseCases/User/CreateTenantUser/CreateTenantUserUseCase.h"
#include "Application/UseCases/User/GetAllTenants/GetAllTenantsUseCase.h"
#include "Application/UseCases/User/RemoveTenant/RemoveTenantUseCase.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include "UI/InputForm.h"
#include "UI/TextEditor.h"
#include "UseCases/User/CreateTenantUser/CreateTenantUserUseCase.h"

TenantController::TenantController(vector<shared_ptr<IUseCase>>& useCases,
                                   shared_ptr<TenantController> tenController){
    for (auto useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
    tenantController = tenController;
}

void TenantController::displayMenu() {
    // Kept for compatibility
    cout << "\Tenant Menu:\n";
    cout << "1. Add Tenant\n";
    cout << "2. Get All Tenants\n";
    cout << "3. Remove Tenant\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void TenantController::createTenant() {
    ConsoleUtils::clearScreen();

    InputForm form("Add New Tenant");
    form.addTextField("Id", "Tenant Id", 20, true)
        .addTextField("username", "Tenant Username", 50, true)
        .addTextField("password", "Password", 50, true)
        .addTextField("nationalId", "Tenant National Id", 20, true)
        .addTextField("phone", "Tenant Phone Number", 100, true)
        .addTextField("name", "Tenant Full Name", 100 , true);
    FormResult result = form.show();

    if (result.submitted) {
        int id = result.get("Id");
        string username = result.get("username");
        string password = result.get("password");
        string nationalId = result.get("nationalId");
        string phone = result.get("phone");
        string name = result.get("name");

        CreateTenantUserParams params = {id,username, password, phone,nationalId, name};

        try {
            useCases["CreateTenantUser"]->execute(params);

            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Tenant created successfully!" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);

            cout << "Id: " << id << endl;
            cout << "UserName: " << username << endl;
            cout << "Full Name: " << name << endl;
            cout << "National Id: " << nationalId << endl;
            cout << "Password: " << password << endl;
            cout << "Phone Number: " << phone << endl;
        }
        catch (const exception& e) {
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\nError: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
        }

        cout << "\nPress any key to continue...";
        ConsoleUtils::getKey();
    }
}

void TenantController::getAllTenants() {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "=== All Tenants ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    auto result = useCases["GetAllTenants"]->execute();
    vector<TenantUser> tenants = any_cast<vector<TenantUser>>(result);

    if (tenants.empty()) {
        cout << "\nNo Tenants found." << endl;
    }
    else {
        cout << "\nTotal Tenants: " << tenants.size() << "\n" << endl;
        for (auto tenant : tenants) {
            cout << "Id: " << tenant.getUserId() << endl;
            cout << "UserName: " << tenant.getUsername() << endl;
            cout << "Full Name: " << tenant.getFullName() << endl;
            cout << "National Id: " << tenant.getNationalId() << endl;
            cout << "Password: " << tenant.getPassword() << endl;
            cout << "Phone Number: " << tenant.getPhoneNumber() << endl;
            cout << "------------------------------------" << endl;
        }
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void TenantController::removeTenant() {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Tenant ID", 10);
    editor.setPosition(2, 2).setInputType(InputType::NUMERIC);

    string idStr = editor.show();
    if (idStr.empty())
        return;
    int id = stoi(idStr);



    try {
        RemoveTenantParams params = { id };
        auto resultAny = useCases["RemoveTenant"]->execute(params);

        bool isDeleted = any_cast<bool>(resultAny);

        ConsoleUtils::clearScreen();
        if (isDeleted) {
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Tenant with ID " << id << " is Deleted." << endl;
        }
        else {
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Tenant with ID " << id << " is not Deleted." << endl;
        }
    } catch (const exception& e) {
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\nError: " << e.what() << endl;
    }

    ConsoleUtils::textattr(Colors::DEFAULT);
    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}


void TenantController::execute() {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Tenant Management", {
            "1. Add Tenant",
            "2. Get All Tenants",
            "3. Remove Tenant",
            "0. Back to Main Menu"
            });

        int choice = menu.show();

        switch (choice) {
        case 0:
            createTenant();
            break;
        case 1:
            getAllTenants();
            break;
        case 2:
            removeTenant();
            break;
        case 3:
        case -1:
            running = false;
            break;
        }
    }
}
