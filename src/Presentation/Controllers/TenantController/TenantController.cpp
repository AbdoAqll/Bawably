#include "TenantController.h"
#include <iostream>
#include "Application/UseCases/User/CreateTenantUser/CreateTenantUserUseCase.h"
#include "Application/UseCases/User/GetAllTenants/GetAllTenantsUseCase.h"
#include "Application/UseCases/User/RemoveTenant/RemoveTenantUseCase.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include "UI/InputForm.h"
#include "UI/TextEditor.h"

TenantController::TenantController(vector<shared_ptr<IUseCase>>& useCases) {
    for (auto useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
}


void TenantController::createTenant() {
    ConsoleUtils::clearScreen();

    InputForm form("Add New Tenant");
    form.addTextField("username", "Tenant Username", 50, true)
        .addTextField("password", "Password", 50, true)
        .addTextField("nationalId", "Tenant National Id", 50, true)
        .addTextField("phone", "Tenant Phone Number", 50, true)
        .addTextField("name", "Tenant Full Name", 50, true);
    FormResult result = form.show();

    if (result.submitted) {
        string username = result.get("username");
        string password = result.get("password");
        string nationalId = result.get("nationalId");
        string phone = result.get("phone");
        string name = result.get("name");

        CreateTenantUserParams params = { username, password, phone,nationalId, name };
        auto res = useCases["CreateTenantUser"]->execute(params);

        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::HIGHLIGHT);
        cout << "\n Tenant created successfully!" << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);

        cout << "Id: " << any_cast<int>(res) << endl;
        cout << "UserName: " << username << endl;
        cout << "Full Name: " << name << endl;
        cout << "National Id: " << nationalId << endl;
        cout << "Password: " << password << endl;
        cout << "Phone Number: " << phone << endl;

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
            cout << "UserName: " << tenant.getUserName() << endl;
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

    auto res = useCases["RemoveTenant"]->execute(RemoveTenantParams{ id });

    bool isDeleted = any_cast<bool>(res);
    ConsoleUtils::clearScreen();
    if (isDeleted) {
        ConsoleUtils::textattr(Colors::HIGHLIGHT);
        cout << "\n Tenant with ID " << id << " is Deleted." << endl;
    }
    else {
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n Tenant with ID " << id << " is not Deleted." << endl;
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
            // "3. Remove Tenant",
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
            // case 2:
            //     removeTenant();
            //     break;
        case 2:
        case -1:
            running = false;
            break;
        }
    }
}
