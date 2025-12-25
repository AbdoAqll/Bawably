#include "IsBuildingExistsUseCase.h"

IsBuildingExistsUseCase::IsBuildingExistsUseCase(shared_ptr<IBuildingRepository> repository) 
: repository(repository) {
    UseCaseName = "IsBuildingExists";
}

any IsBuildingExistsUseCase::execute(const any& params) {
    auto id = any_cast<int>(params);
    return repository->exists(id);
}
