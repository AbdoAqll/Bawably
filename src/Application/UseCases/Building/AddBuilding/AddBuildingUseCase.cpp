#include "AddBuildingUseCase.h"

AddBuildingUseCase::AddBuildingUseCase(shared_ptr<IBuildingRepository> repository)
    : repository(repository) {
    UseCaseName = "AddBuilding";
}

any AddBuildingUseCase::execute(const any& params)
{
    auto args = any_cast<AddBuildingParams>(params);
    Building building(args.name, args.address);
    repository->save(building);
    return {};
}
