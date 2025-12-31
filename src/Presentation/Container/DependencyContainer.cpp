#include "DependencyContainer.h"

#include <Apartment/Repositories/InMemoryApartmentRepository.h>
#include <UseCases/Apartment/AddApartment/AddApartmentUseCase.h>
#include <UseCases/Apartment/CheckApartmentStatus/CheckApartmentStatusUseCase.h>
#include <UseCases/Apartment/GetAllApartments/GetAllApartmentsUseCase.h>
#include <UseCases/Apartment/GetApartmentDetails/GetApartmentDetailsUseCase.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
#include <UseCases/Apartment/IsApartmentExists/IsApartmentExistsUseCase.h>
#include <UseCases/Apartment/CheckApartmentExistsAndGetId/CheckApartmentExistsAndGetIdUseCase.h>
#include <UseCases/RentalContract/GetRentalContractByTenantId/GetRentalContractByTenantIdUseCase.h>

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

#include "Infrastructure/RentPayment/Repositories/InMemoryRentPaymentRepository.h"
#include "Application/UseCases/RentPayment/RecordRentPayment/RecordRentPaymentUseCase.h"
#include "Application/UseCases/RentPayment/AddPartialPayment/AddPartialPaymentUseCase.h"
#include "Application/UseCases/RentPayment/ViewPaidTenants/ViewPaidTenantsUseCase.h"
#include "Application/UseCases/RentPayment/ViewUnpaidOrPartialTenants/ViewUnpaidOrPartialTenantsUseCase.h"
#include "UseCases/User/GetAllTenants/GetAllTenantsUseCase.h"
#include "UseCases/User/RemoveTenant/RemoveTenantUseCase.h"


using namespace std;

DependencyContainer::DependencyContainer() {
    auto buildingRepository = make_shared<BuildingRepository>();
    shared_ptr<IApartmentRepository> apartmentRepository = make_shared<InMemoryApartmentRepository>();
    shared_ptr<IRentalContractRepository> rentalContractRepository = make_shared<InMemoryRentalContractRepository>();
    shared_ptr<IMaintenanceRequestRepository> maintenanceRequestRepository = make_shared<InMemoryMaintenanceRequestRepository>();
    shared_ptr<IUserRepository> userRepository = make_shared<InMemoryUserRepository>();
    shared_ptr<IRentPaymentRepository> rentPaymentRepository = make_shared<InMemoryRentPaymentRepository>();


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

    vector<shared_ptr<IUseCase>> tenantUseCases = {
        make_shared<CreateTenantUserUseCase>(userRepository),
        make_shared<GetAllTenantsUseCase>(userRepository),
        make_shared<RemoveTenantUseCase>(userRepository)
    };

    auto loginUseCase = make_shared<LoginUseCase>(userRepository);

    auto createRentalContractUseCase = make_shared<CreateRentalContractUseCase>(
        rentalContractRepository, apartmentRepository, userRepository);
    auto endRentalContractUseCase = make_shared<EndRentalContractUseCase>(
        rentalContractRepository, apartmentRepository);
    auto getRentalContractByTenantId = make_shared<GetRentalContractByTenantIdUseCase>(rentalContractRepository, userRepository);

    // Rent Payment Use Cases
    auto recordRentPaymentUseCase = make_shared<RecordRentPaymentUseCase>(
        rentPaymentRepository, rentalContractRepository);
    auto addPartialPaymentUseCase = make_shared<AddPartialPaymentUseCase>(
        rentPaymentRepository, rentalContractRepository);
    auto viewPaidTenantsUseCase = make_shared<ViewPaidTenantsUseCase>(
        rentPaymentRepository, rentalContractRepository, userRepository, apartmentRepository);
    auto viewUnpaidOrPartialTenantsUseCase = make_shared<ViewUnpaidOrPartialTenantsUseCase>(
        rentPaymentRepository, rentalContractRepository, userRepository, apartmentRepository);

    // Initialize controllers
    authController = make_shared<AuthController>(loginUseCase);
    rentalContractController = make_shared<RentalContractController>(
        createRentalContractUseCase, endRentalContractUseCase, getRentalContractByTenantId, rentalContractRepository);
    rentPaymentController = make_shared<RentPaymentController>(
        recordRentPaymentUseCase, addPartialPaymentUseCase,
        viewPaidTenantsUseCase, viewUnpaidOrPartialTenantsUseCase, rentPaymentRepository);
    maintenanceRequestController = make_shared<MaintenanceRequestController>(maintenanceRequestUseCases);
    apartmentController = make_shared<ApartmentController>(apartmentUseCases, rentalContractController);
    buildingController = make_shared<BuildingController>(buildingUseCases, apartmentController, maintenanceRequestController);
    tenantController = make_shared<TenantController>(tenantUseCases);

    // Initialize menu controllers
    ownerMenuController = make_shared<OwnerMenuController>(buildingController, rentPaymentController, tenantController);
    tenantMenuController = make_shared<TenantMenuController>(maintenanceRequestController, apartmentRepository);

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

std::shared_ptr<RentPaymentController> DependencyContainer::getRentPaymentController() {
    return rentPaymentController;
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

std::shared_ptr<TenantController> DependencyContainer::getTenantController() {
    return tenantController;
}

