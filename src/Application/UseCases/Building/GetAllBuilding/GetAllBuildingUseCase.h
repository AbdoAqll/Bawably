#ifndef GET_ALL_BUILDING_H
#define GET_ALL_BUILDING_H

#include <string>
#include <vector>
#include <memory>
#include "../../IUseCase.h"
#include "../Interfaces/IBuildingRepository.h"
#include "Domain/Building/Building.h"

using namespace std;

class GetAllBuildingUseCase :public IUseCase {
    shared_ptr<IBuildingRepository> repository;
public:
    GetAllBuildingUseCase(shared_ptr<IBuildingRepository> repository);
    any execute(const any& params = {}) override;
    ~GetAllBuildingUseCase() override = default;
};

#endif
