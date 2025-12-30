#ifndef I_BUILDING_REPOSITORY_H
#define I_BUILDING_REPOSITORY_H

#include "Domain/Building/Building.h"
#include <vector>
using namespace std;

class IBuildingRepository
{
public:
    virtual ~IBuildingRepository() = default;

    virtual bool save(const Building &building) = 0;
    virtual Building findById(int id) = 0;
    virtual bool exists(int id) = 0;
    virtual vector<Building> getAll() = 0;
};

#endif
