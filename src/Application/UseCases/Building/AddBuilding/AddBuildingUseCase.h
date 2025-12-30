#ifndef ADD_BUILDING_H
#define ADD_BUILDING_H

#include <string>
#include <memory>
#include "../../IUseCase.h"
#include "../Interfaces/IBuildingRepository.h"

using namespace std;
struct AddBuildingParams {
    string name;
    string address;
};

class AddBuildingUseCase : public IUseCase
{
    shared_ptr<IBuildingRepository> repository;
public:
    AddBuildingUseCase(shared_ptr<IBuildingRepository> repository);
    any execute(const any& params = {}) override;
    ~AddBuildingUseCase() override = default;
};

#endif // ADD_BUILDING_H