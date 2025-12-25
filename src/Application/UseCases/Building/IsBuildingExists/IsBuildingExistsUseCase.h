#ifndef IS_BUILDING_EXISTS_H
#define IS_BUILDING_EXISTS_H

#include <string>
#include <memory>
#include "../../IUseCase.h"
#include "../Interfaces/IBuildingRepository.h"

using namespace std;

class IsBuildingExistsUseCase : public IUseCase {
    shared_ptr<IBuildingRepository> repository;
public:
    IsBuildingExistsUseCase(shared_ptr<IBuildingRepository> repository);
    any execute(const any& params = {}) override;
    ~IsBuildingExistsUseCase() override = default;
};

#endif // IS_BUILDING_EXISTS_H
