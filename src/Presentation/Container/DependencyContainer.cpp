#include "DependencyContainer.h"

#include <Apartment/Repositories/InMemoryApartmentRepository.h>
#include <UseCases/Apartment/AddApartment/AddApartmentUseCase.h>
#include <UseCases/Apartment/CheckApartmentStatus/CheckApartmentStatusUseCase.h>
#include <UseCases/Apartment/GetAllApartments/GetAllApartmentsUseCase.h>
#include <UseCases/Apartment/GetApartmentDetails/GetApartmentDetailsUseCase.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
#include <UseCases/Apartment/IsApartmentExists/IsApartmentExistsUseCase.h>

#include "Infrastructure/User/Repositories/UserRepository.h"
#include "Infrastructure/Building/Repositories/BuildingRepository.h"
#include "Infrastructure/RentalContract/Repositories/InMemoryRentalContractRepository.h"
#include "Infrastructure/Tenant/Repositories/InMemoryTenantRepository.h"

#include "Application/UseCases/Building/AddBuilding/AddBuildingUseCase.h"
#include "Application/UseCases/Building/GetAllBuilding/GetAllBuildingUseCase.h"
#include "Application/UseCases/Building/GetBuildingDetails/GetBuildingDetailsUseCase.h"
#include "Application/UseCases/Building/IsBuildingExists/IsBuildingExistsUseCase.h"

#include "Application/UseCases/RentalContract/CreateRentalContract/CreateRentalContractUseCase.h"
#include "Application/UseCases/RentalContract/EndRentalContract/EndRentalContractUseCase.h"

using namespace std;

DependencyContainer::DependencyContainer() {
    auto userRepository = make_shared<UserRepository>();
    auto buildingRepository = make_shared<BuildingRepository>();
    shared_ptr<IApartmentRepository> apartmentRepository = make_shared<InMemoryApartmentRepository>();
    shared_ptr<IRentalContractRepository> rentalContractRepository = make_shared<InMemoryRentalContractRepository>();
    shared_ptr<ITenantRepository> tenantRepository = make_shared<InMemoryTenantRepository>();

    auto createUserUseCase = make_shared<CreateUserUseCase>(userRepository);

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
        make_shared<IsApartmentExistsUseCase>(apartmentRepository, buildingRepository)
    };

    auto createRentalContractUseCase = make_shared<CreateRentalContractUseCase>(
        rentalContractRepository, apartmentRepository, tenantRepository);
    auto endRentalContractUseCase = make_shared<EndRentalContractUseCase>(
        rentalContractRepository, apartmentRepository);

    userController = make_shared<UserController>(createUserUseCase);
    buildingController = make_shared<BuildingController>(buildingUseCases);
    apartmentController = make_shared<ApartmentController>(apartmentUseCases);
    rentalContractController = make_shared<RentalContractController>(
        createRentalContractUseCase, endRentalContractUseCase, rentalContractRepository);
}

shared_ptr<UserController> DependencyContainer::getUserController() {
    return userController;
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

