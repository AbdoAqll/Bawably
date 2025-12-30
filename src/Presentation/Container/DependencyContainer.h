#ifndef DEPENDENCY_CONTAINER_H
#define DEPENDENCY_CONTAINER_H

#include <memory>
#include <vector>
#include <Controllers/ApartmentController/ApartmentController.h>
#include "Controllers/BuildingController/BuildingController.h"
#include "Controllers/MaintenanceRequestController/MaintenanceRequestController.h"
#include "Controllers/RentalContractController/RentalContractController.h"
#include "Controllers/RentPaymentController/RentPaymentController.h"
#include "Controllers/AuthController/AuthController.h"
#include "Controllers/OwnerMenuController/OwnerMenuController.h"
#include "Controllers/TenantMenuController/TenantMenuController.h"
#include "Application/UseCases/IUseCase.h"

class DependencyContainer {
    std::shared_ptr<BuildingController> buildingController;
    std::shared_ptr<ApartmentController> apartmentController;
    std::shared_ptr<RentalContractController> rentalContractController;
    std::shared_ptr<RentPaymentController> rentPaymentController;
    std::shared_ptr<MaintenanceRequestController> maintenanceRequestController;
    std::shared_ptr<AuthController> authController;
    std::shared_ptr<OwnerMenuController> ownerMenuController;
    std::shared_ptr<TenantMenuController> tenantMenuController;

public:
    DependencyContainer();
    std::shared_ptr<BuildingController> getBuildingController();
    std::shared_ptr<ApartmentController> getApartmentController();
    std::shared_ptr<RentalContractController> getRentalContractController();
    std::shared_ptr<RentPaymentController> getRentPaymentController();
    std::shared_ptr<MaintenanceRequestController> getMaintenanceRequestController();
    std::shared_ptr<AuthController> getAuthController();
    std::shared_ptr<OwnerMenuController> getOwnerMenuController();
    std::shared_ptr<TenantMenuController> getTenantMenuController();
};

#endif
