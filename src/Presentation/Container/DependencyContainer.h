#ifndef DEPENDENCY_CONTAINER_H
#define DEPENDENCY_CONTAINER_H

#include <memory>
#include <vector>
#include "Controllers/UserController.h"
#include "Controllers/BuildingController/BuildingController.h" 
#include "Application/UseCases/IUseCase.h" 

class DependencyContainer {
    std::shared_ptr<UserController> userController;
    std::shared_ptr<BuildingController> buildingController;
public:
    DependencyContainer();
    std::shared_ptr<UserController> getUserController();
    std::shared_ptr<BuildingController> getBuildingController();
};

#endif
