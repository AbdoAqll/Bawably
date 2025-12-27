#include "BuildingController.h"
#include <iostream>
#include "Application/UseCases/Building/AddBuilding/AddBuildingUseCase.h"
#include "Application/UseCases/Building/GetAllBuilding/GetAllBuildingUseCase.h"
#include "Application/UseCases/Building/GetBuildingDetails/GetBuildingDetailsUseCase.h"
#include "Application/UseCases/Building/IsBuildingExists/IsBuildingExistsUseCase.h"
BuildingController::BuildingController(vector<shared_ptr<IUseCase>>& useCases) 
{
    for (auto useCase : useCases) {
        this->useCases[useCase->UseCaseName] = useCase;
    }
}
void BuildingController::displayMenu() {
    cout << "\nBuilding Menu:\n";
    cout << "1. Add Building\n";
    cout << "2. Manage Building\n"; // apartment/maintenance (building only)
    // first take the id of the building them start to pass it to all the controllers of the other modules
    cout << "3. Get All Buildings\n";
    cout << "4. Get Building Details\n";
    cout << "5. Check if Building Exists\n";
    cout << "0. Exit\n";
    cout << "Enter your choice: ";
}

void BuildingController::createBuilding() {
    string name, address;
    cout << "Enter Building Name: ";
    getline(cin, name);
    cout << "Enter Building Address: ";
    getline(cin, address);
    
    AddBuildingParams params = {name, address};
    useCases["AddBuilding"]->execute(params);
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
    } catch (const exception& e) {
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
    } else {
        cout << "Building with ID " << id << " does not exist.\n";
    }
}
void BuildingController::execute() {
    int choice = 0;
    while(true) {
        displayMenu();
        cin >> choice;
        cin.ignore();
        switch(choice) {
            case 1: 
                createBuilding(); 
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
            case 0: 
                return;
            default: 
                cout << "Invalid choice.\n";
        }
    }
}
