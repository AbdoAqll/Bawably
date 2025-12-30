#include "GetBuildingDetailsUseCase.h"

GetBuildingDetailsUseCase::GetBuildingDetailsUseCase(shared_ptr<IBuildingRepository> repository) 
: repository(repository) {
    UseCaseName = "GetBuildingDetails";
}

any GetBuildingDetailsUseCase::execute(const any& params) {
    auto id = any_cast<int>(params);
    Building building = repository->findById(id);
    return building;
}