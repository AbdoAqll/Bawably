#ifndef GET_BUILDING_DETAILS_H
#define GET_BUILDING_DETAILS_H

#include <string>
#include <memory>
#include "../../IUseCase.h"
#include "../Interfaces/IBuildingRepository.h"
#include "Domain/Building/Building.h"

using namespace std;

class GetBuildingDetailsUseCase :public IUseCase {
    shared_ptr<IBuildingRepository> repository;
public:
    GetBuildingDetailsUseCase(shared_ptr<IBuildingRepository> repository);
    any execute(const any& params = {}) override;
    ~GetBuildingDetailsUseCase() override = default;
};

#endif 