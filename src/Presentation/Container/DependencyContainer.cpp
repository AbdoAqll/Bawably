#include "DependencyContainer.h"
#include "Infrastructure/User/Repositories/UserRepository.h"
#include "Infrastructure/Building/Repositories/BuildingRepository.h"
#include "Application/UseCases/Building/AddBuilding/AddBuildingUseCase.h"
#include "Application/UseCases/Building/GetAllBuilding/GetAllBuildingUseCase.h"
#include "Application/UseCases/Building/GetBuildingDetails/GetBuildingDetailsUseCase.h"
#include "Application/UseCases/Building/IsBuildingExists/IsBuildingExistsUseCase.h"

using namespace std;

DependencyContainer::DependencyContainer() {
    auto userRepository = make_shared<UserRepository>();
    auto buildingRepository = make_shared<BuildingRepository>();
    
    auto createUserUseCase = make_shared<CreateUserUseCase>(userRepository);
    
    vector<shared_ptr<IUseCase>> buildingUseCases = {
        make_shared<AddBuildingUseCase>(buildingRepository),
        make_shared<GetAllBuildingUseCase>(buildingRepository),
        make_shared<GetBuildingDetailsUseCase>(buildingRepository),
        make_shared<IsBuildingExistsUseCase>(buildingRepository)
    };
   
    userController = make_shared<UserController>(createUserUseCase);
    buildingController = make_shared<BuildingController>(buildingUseCases);
}

shared_ptr<UserController> DependencyContainer::getUserController() {
    return userController;
}

shared_ptr<BuildingController> DependencyContainer::getBuildingController() {
    return buildingController;
}
