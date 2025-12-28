#ifndef DEPENDENCY_CONTAINER_H
#define DEPENDENCY_CONTAINER_H

#include <memory>
#include <vector>
#include <Controllers/ApartmentController/ApartmentController.h>

#include "Controllers/UserController.h"
#include "Controllers/BuildingController/BuildingController.h"
#include "Controllers/MaintenanceRequestController/MaintenanceRequestController.h"
#include "Application/UseCases/IUseCase.h" 

class DependencyContainer {
    std::shared_ptr<UserController> userController;
    std::shared_ptr<BuildingController> buildingController;
    std::shared_ptr<ApartmentController> apartmentController;
    std::shared_ptr<MaintenanceRequestController> maintenanceRequestController;

public:
    DependencyContainer();
    std::shared_ptr<UserController> getUserController();
    std::shared_ptr<BuildingController> getBuildingController();
    std::shared_ptr<ApartmentController> getApartmentController();
    std::shared_ptr<MaintenanceRequestController> getMaintenanceRequestController();
};

#endif
