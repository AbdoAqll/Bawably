#include "DependencyContainer.h"

#include <Apartment/Repositories/InMemoryApartmentRepository.h>
#include <UseCases/Apartment/AddApartment/AddApartmentUseCase.h>
#include <UseCases/Apartment/CheckApartmentStatus/CheckApartmentStatusUseCase.h>
#include <UseCases/Apartment/GetAllApartments/GetAllApartmentsUseCase.h>
#include <UseCases/Apartment/GetApartmentDetails/GetApartmentDetailsUseCase.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
#include <UseCases/Apartment/IsApartmentExists/IsApartmentExistsUseCase.h>
#include <UseCases/Apartment/CheckApartmentExistsAndGetId/CheckApartmentExistsAndGetIdUseCase.h>

#include "Infrastructure/Building/Repositories/BuildingRepository.h"
#include "Application/UseCases/Building/AddBuilding/AddBuildingUseCase.h"
#include "Application/UseCases/Building/GetAllBuilding/GetAllBuildingUseCase.h"
#include "Application/UseCases/Building/GetBuildingDetails/GetBuildingDetailsUseCase.h"
#include "Application/UseCases/Building/IsBuildingExists/IsBuildingExistsUseCase.h"

#include "Infrastructure/RentalContract/Repositories/InMemoryRentalContractRepository.h"
#include "Application/UseCases/RentalContract/CreateRentalContract/CreateRentalContractUseCase.h"
#include "Application/UseCases/RentalContract/EndRentalContract/EndRentalContractUseCase.h"

#include "Infrastructure/MaintenanceRequest/Repositories/InMemoryMaintenanceRequestRepository.h"
#include "Application/UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h"
#include "Application/UseCases/MaintenanceRequest/AddMaintenanceRequest/AddMaintenanceRequestUseCase.h"
#include "Application/UseCases/MaintenanceRequest/ViewBuildingMaintenanceRequests/ViewBuildingMaintenanceRequestsUseCase.h"
#include "Application/UseCases/MaintenanceRequest/ViewApartmentMaintenanceRequests/ViewApartmentMaintenanceRequestsUseCase.h"
#include "Application/UseCases/MaintenanceRequest/CloseMaintenanceRequest/CloseMaintenanceRequestUseCase.h"

#include "Infrastructure/User/Repositories/InMemoryUserRepository.h"
#include "Application/UseCases/User/Login/LoginUseCase.h"
#include "Application/UseCases/User/CreateTenantUser/CreateTenantUserUseCase.h"


using namespace std;

DependencyContainer::DependencyContainer() {
    auto buildingRepository = make_shared<BuildingRepository>();
    shared_ptr<IApartmentRepository> apartmentRepository = make_shared<InMemoryApartmentRepository>();
    shared_ptr<IRentalContractRepository> rentalContractRepository = make_shared<InMemoryRentalContractRepository>();
    shared_ptr<IMaintenanceRequestRepository> maintenanceRequestRepository = make_shared<InMemoryMaintenanceRequestRepository>();
    shared_ptr<IUserRepository> userRepository = make_shared<InMemoryUserRepository>();


    vector<shared_ptr<IUseCase>> buildingUseCases = {
        make_shared<AddBuildingUseCase>(buildingRepository),
        make_shared<GetAllBuildingUseCase>(buildingRepository),
        make_shared<GetBuildingDetailsUseCase>(buildingRepository),
        make_shared<IsBuildingExistsUseCase>(buildingRepository)
    };

    vector<shared_ptr<IUseCase>> apartmentUseCases = {
        make_shared<AddApartmentUseCase>(apartmentRepository, buildingRepository),
        make_shared<CheckApartmentStatusUseCase>(apartmentRepository, buildingRepository),
        make_shared<GetAllApartmentsUseCase>(apartmentRepository, buildingRepository),
        make_shared<GetApartmentDetailsUseCase>(apartmentRepository, buildingRepository),
        make_shared<IsApartmentExistsUseCase>(apartmentRepository, buildingRepository),
        make_shared<CheckApartmentExistsAndGetIdUseCase>(apartmentRepository, buildingRepository)
    };

    vector<shared_ptr<IUseCase>> maintenanceRequestUseCases = {
        make_shared<AddMaintenanceRequestUseCase>(maintenanceRequestRepository,apartmentRepository,buildingRepository),
        make_shared<ViewBuildingMaintenanceRequestsUseCase>(maintenanceRequestRepository, buildingRepository),
        make_shared<ViewApartmentMaintenanceRequestsUseCase>(maintenanceRequestRepository),
        make_shared<CloseMaintenanceRequestUseCase>(maintenanceRequestRepository)
    };

    auto loginUseCase = make_shared<LoginUseCase>(userRepository);

    auto createRentalContractUseCase = make_shared<CreateRentalContractUseCase>(
        rentalContractRepository, apartmentRepository, userRepository);
    auto endRentalContractUseCase = make_shared<EndRentalContractUseCase>(
        rentalContractRepository, apartmentRepository);

    // Initialize controllers
    authController = make_shared<AuthController>(loginUseCase);
    rentalContractController = make_shared<RentalContractController>(
        createRentalContractUseCase, endRentalContractUseCase, rentalContractRepository);
    maintenanceRequestController = make_shared<MaintenanceRequestController>(maintenanceRequestUseCases);
    apartmentController = make_shared<ApartmentController>(apartmentUseCases, rentalContractController);
    buildingController = make_shared<BuildingController>(buildingUseCases, apartmentController, maintenanceRequestController);

    // Initialize menu controllers
    ownerMenuController = make_shared<OwnerMenuController>(buildingController);
    tenantMenuController = make_shared<TenantMenuController>(maintenanceRequestController);
}


shared_ptr<BuildingController> DependencyContainer::getBuildingController() {
    return buildingController;
}

std::shared_ptr<ApartmentController> DependencyContainer::getApartmentController() {
    return apartmentController;
}

std::shared_ptr<RentalContractController> DependencyContainer::getRentalContractController() {
    return rentalContractController;
}

std::shared_ptr<MaintenanceRequestController> DependencyContainer::getMaintenanceRequestController() {
    return maintenanceRequestController;
}

std::shared_ptr<AuthController> DependencyContainer::getAuthController() {
    return authController;
}

std::shared_ptr<OwnerMenuController> DependencyContainer::getOwnerMenuController() {
    return ownerMenuController;
}

std::shared_ptr<TenantMenuController> DependencyContainer::getTenantMenuController() {
    return tenantMenuController;
}

