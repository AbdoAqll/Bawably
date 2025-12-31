#ifndef BUILDING_REPOSITORY_H
#define BUILDING_REPOSITORY_H

#include "Domain/Building/Building.h"
#include <unordered_map>
#include "Application/UseCases/Building/Interfaces/IBuildingRepository.h"
using namespace std;

class BuildingRepository : public IBuildingRepository {
private:
    unordered_map<int, Building> buildings;
public:
    BuildingRepository();
    ~BuildingRepository() = default;

    bool save(const Building& building) override;
    Building findById(int id) override;
    bool exists(int id) override;
    vector<Building> getAll() override;
};

#endif