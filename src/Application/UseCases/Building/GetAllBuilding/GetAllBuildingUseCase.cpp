#include "GetAllBuildingUseCase.h"


GetAllBuildingUseCase::GetAllBuildingUseCase(shared_ptr<IBuildingRepository> repository) 
: repository(repository) {
    UseCaseName = "GetAllBuilding";
}

any GetAllBuildingUseCase::execute(const any& params) {
    vector<Building> buildings = repository->getAll();
    return buildings;
}