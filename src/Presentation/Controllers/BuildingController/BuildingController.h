#ifndef BUILDING_CONTROLLER_H
#define BUILDING_CONTROLLER_H

#include <string>
#include <unordered_map>
#include <vector>
#include <memory>
#include "../Application/UseCases/IUseCase.h"

using namespace std;

class BuildingController
{
    unordered_map<string, shared_ptr<IUseCase>> useCases;

public:
    BuildingController(vector<shared_ptr<IUseCase>> &useCases);
    void displayMenu();
    void createBuilding();
    void getAllBuildings();
    void getBuildingDetails();
    void isBuildingExists();
    void execute();
    ~BuildingController() = default;
};

#endif