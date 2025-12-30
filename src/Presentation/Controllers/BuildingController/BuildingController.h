#ifndef BUILDING_CONTROLLER_H
#define BUILDING_CONTROLLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "../Application/UseCases/IUseCase.h"

using namespace std;

class ApartmentController;
class MaintenanceRequestController;

class BuildingController {
    unordered_map<string, shared_ptr<IUseCase>> useCases;
    shared_ptr<ApartmentController> apartmentController;
    shared_ptr<MaintenanceRequestController> maintenanceRequestController;

public:
    BuildingController(vector<shared_ptr<IUseCase>>& useCases,
        shared_ptr<ApartmentController> apartmentController,
        shared_ptr<MaintenanceRequestController> maintenanceRequestController);
    void displayMenu();
    void createBuilding();
    void manageBuilding();
    void displayManageBuildingMenu(int buildingId);
    void getAllBuildings();
    void getBuildingDetails();
    void isBuildingExists();
    void execute();
    ~BuildingController() = default;
};

#endif