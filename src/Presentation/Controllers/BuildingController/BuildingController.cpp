#include "BuildingController.h"
#include <iostream>
#include "Application/UseCases/Building/AddBuilding/AddBuildingUseCase.h"
#include "Application/UseCases/Building/GetAllBuilding/GetAllBuildingUseCase.h"
#include "Application/UseCases/Building/GetBuildingDetails/GetBuildingDetailsUseCase.h"
#include "Application/UseCases/Building/IsBuildingExists/IsBuildingExistsUseCase.h"
#include "Controllers/ApartmentController/ApartmentController.h"
#include "Controllers/MaintenanceRequestController/MaintenanceRequestController.h"

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
    string name, address;
    cout << "Enter Building Name: ";
    getline(cin, name);
    cout << "Enter Building Address: ";
    getline(cin, address);

    AddBuildingParams params = { name, address };
    useCases["AddBuilding"]->execute(params);
}

void BuildingController::manageBuilding() {
    int buildingId;
    cout << "Enter Building ID to manage: ";
    cin >> buildingId;
    cin.ignore();

    // Verify building exists
    auto result = useCases["IsBuildingExists"]->execute(buildingId);
    bool exists = any_cast<bool>(result);
    if (!exists) {
        cout << "Building with ID " << buildingId << " does not exist.\n";
        return;
    }

    displayManageBuildingMenu(buildingId);
}

void BuildingController::displayManageBuildingMenu(int buildingId) {
    int choice = 0;
    while (true) {
        cout << "\n=== Manage Building (ID: " << buildingId << ") ===\n";
        cout << "1. Apartment Management\n";
        cout << "2. Maintenance Management\n";
        cout << "0. Back to Building Menu\n";
        cout << "Enter your choice: ";
        cin >> choice;
        cin.ignore();

        switch (choice) {
        case 1:
            apartmentController->execute(buildingId);
            break;
        case 2:
            maintenanceRequestController->execute(buildingId);
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice.\n";
        }
    }
}

void BuildingController::getAllBuildings() {
    auto result = useCases["GetAllBuilding"]->execute();
    vector<Building> buildings = any_cast<vector<Building>>(result);
    for (auto building : buildings) {
        cout << "ID: " << building.getId() << ", Name: " << building.getName() << ", Address: " << building.getAddress() << endl;
    }
}
void BuildingController::getBuildingDetails() {
    int id;
    cout << "Enter Building ID: ";
    cin >> id;
    cin.ignore();
    try {
        auto result = useCases["GetBuildingDetails"]->execute(id);
        Building building = any_cast<Building>(result);
        cout << "ID: " << building.getId() << ", Name: " << building.getName() << ", Address: " << building.getAddress() << endl;
    }
    catch (const exception& e) {
        cout << e.what() << endl;
    }
}
void BuildingController::isBuildingExists() {
    int id;
    cout << "Enter Building ID: ";
    cin >> id;
    cin.ignore();
    auto result = useCases["IsBuildingExists"]->execute(id);
    bool exists = any_cast<bool>(result);
    if (exists) {
        cout << "Building with ID " << id << " exists.\n";
    }
    else {
        cout << "Building with ID " << id << " does not exist.\n";
    }
}
void BuildingController::execute() {
    int choice = 0;
    while (true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        switch (choice) {
        case 1:
            createBuilding();
            break;
        case 2:
            manageBuilding();
            break;
        case 3:
            getAllBuildings();
            break;
        case 4:
            getBuildingDetails();
            break;
        case 5:
            isBuildingExists();
            break;
        case 0:
            return;
        default:
            cout << "Invalid choice.\n";
        }
    }
}
