#include "BuildingController.h"
#include <iostream>
#include "Application/UseCases/Building/AddBuilding/AddBuildingUseCase.h"
#include "Application/UseCases/Building/GetAllBuilding/GetAllBuildingUseCase.h"
#include "Application/UseCases/Building/GetBuildingDetails/GetBuildingDetailsUseCase.h"
#include "Application/UseCases/Building/IsBuildingExists/IsBuildingExistsUseCase.h"
#include "Controllers/ApartmentController/ApartmentController.h"
#include "Controllers/MaintenanceRequestController/MaintenanceRequestController.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include "UI/InputForm.h"
#include "UI/TextEditor.h"

BuildingController::BuildingController(vector<shared_ptr<IUseCase>>& useCases,
    shared_ptr<ApartmentController> apartmentCtrl,
    shared_ptr<MaintenanceRequestController> maintenanceCtrl) {
    for (auto useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
    apartmentController = apartmentCtrl;
    maintenanceRequestController = maintenanceCtrl;
}

void BuildingController::displayMenu() {
    // Kept for compatibility
    cout << "\nBuilding Menu:\n";
    cout << "1. Add Building\n";
    cout << "2. Manage Building\n";
    cout << "3. Get All Buildings\n";
    cout << "4. Get Building Details\n";
    cout << "5. Check if Building Exists\n";
    cout << "0. Back to Main Menu\n";
    cout << "Enter your choice: ";
}

void BuildingController::createBuilding() {
    ConsoleUtils::clearScreen();

    InputForm form("Add New Building");
    form.addTextField("name", "Building Name", 20, true)
        .addTextField("address", "Building Address", 50, true);

    FormResult result = form.show();

    if (result.submitted) {
        string name = result.get("name");
        string address = result.get("address");

        AddBuildingParams params = { name, address };
        useCases["AddBuilding"]->execute(params);

        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::HIGHLIGHT);
        cout << "\n Building created successfully!" << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "Name: " << name << endl;
        cout << "Address: " << address << endl;
        cout << "\nPress any key to continue...";
        ConsoleUtils::getKey();
    }
}

void BuildingController::manageBuilding() {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Building ID to manage", 10);
    editor.setPosition(2, 2).setInputType(InputType::NUMERIC);

    string idStr = editor.show();

    if (idStr.empty()) return;

    int buildingId = stoi(idStr);

    // Verify building exists
    auto result = useCases["IsBuildingExists"]->execute(buildingId);
    bool exists = any_cast<bool>(result);
    if (!exists) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n Building with ID " << buildingId << " does not exist." << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "\nPress any key to continue...";
        ConsoleUtils::getKey();
        return;
    }

    displayManageBuildingMenu(buildingId);
}

void BuildingController::displayManageBuildingMenu(int buildingId) {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Manage Building (ID: " + to_string(buildingId) + ")", vector<string>{
            "1. Apartment Management",
                "2. Maintenance Management",
                "0. Back to Building Menu"
        });

        int choice = menu.show();

        switch (choice) {
        case 0:
            apartmentController->execute(buildingId);
            break;
        case 1:
            maintenanceRequestController->executeForOwner(buildingId);
            break;
        case 2:
        case -1:
            running = false;
            break;
        }
    }
}

void BuildingController::getAllBuildings() {
    ConsoleUtils::clearScreen();
    ConsoleUtils::textattr(Colors::TITLE);
    cout << "=== All Buildings ===" << endl;
    ConsoleUtils::textattr(Colors::DEFAULT);

    auto result = useCases["GetAllBuilding"]->execute();
    vector<Building> buildings = any_cast<vector<Building>>(result);

    if (buildings.empty()) {
        cout << "\nNo buildings found." << endl;
    }
    else {
        cout << "\nTotal Buildings: " << buildings.size() << "\n" << endl;
        for (auto building : buildings) {
            cout << "ID: " << building.getId() << endl;
            cout << "Name: " << building.getName() << endl;
            cout << "Address: " << building.getAddress() << endl;
            cout << "------------------------------------" << endl;
        }
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void BuildingController::getBuildingDetails() {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Building ID", 10);
    editor.setPosition(2, 2).setInputType(InputType::NUMERIC);

    string idStr = editor.show();

    if (idStr.empty()) return;

    int id = stoi(idStr);

    try {
        auto result = useCases["GetBuildingDetails"]->execute(id);
        Building building = any_cast<Building>(result);

        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::TITLE);
        cout << "=== Building Details ===" << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
        cout << "ID: " << building.getId() << endl;
        cout << "Name: " << building.getName() << endl;
        cout << "Address: " << building.getAddress() << endl;
    }
    catch (const exception& e) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n " << e.what() << endl;
        ConsoleUtils::textattr(Colors::DEFAULT);
    }

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void BuildingController::isBuildingExists() {
    ConsoleUtils::clearScreen();

    SingleLineEditor editor("Building ID", 10);
    editor.setPosition(2, 2).setInputType(InputType::NUMERIC);

    string idStr = editor.show();

    if (idStr.empty()) return;

    int id = stoi(idStr);

    auto result = useCases["IsBuildingExists"]->execute(id);
    bool exists = any_cast<bool>(result);

    ConsoleUtils::clearScreen();
    if (exists) {
        ConsoleUtils::textattr(Colors::HIGHLIGHT);
        cout << "\n Building with ID " << id << " exists." << endl;
    }
    else {
        ConsoleUtils::textattr(Colors::ERR);
        cout << "\n Building with ID " << id << " does not exist." << endl;
    }
    ConsoleUtils::textattr(Colors::DEFAULT);

    cout << "\nPress any key to continue...";
    ConsoleUtils::getKey();
}

void BuildingController::execute() {
    bool running = true;

    while (running) {
        MenuDisplayer menu("Building Management", {
            "1. Add Building",
            "2. Manage Building",
            "3. Get All Buildings",
            "4. Get Building Details",
            "5. Check if Building Exists",
            "0. Back to Main Menu"
            });

        int choice = menu.show();

        switch (choice) {
        case 0:
            createBuilding();
            break;
        case 1:
            manageBuilding();
            break;
        case 2:
            getAllBuildings();
            break;
        case 3:
            getBuildingDetails();
            break;
        case 4:
            isBuildingExists();
            break;
        case 5:
        case -1:
            running = false;
            break;
        }
    }
}
