#include "BuildingRepository.h"
#include "Domain/Building/Exceptions/BuildingNotExistException.h"
#include <string>

bool BuildingRepository::save(const Building& building) {
    int id = building.getId();
    auto it = buildings.find(id);
    if (it != buildings.end()) {
        it->second = building;
    }
    else {
        buildings.insert({ id, building });
    }
    return true;
}

Building BuildingRepository::findById(int id) {
    auto it = buildings.find(id);
    if (it != buildings.end()) {
        return it->second;
    }
    throw BuildingNotExistException(id);
}

bool BuildingRepository::exists(int id) {
    return buildings.find(id) != buildings.end();
}

vector<Building> BuildingRepository::getAll() {
    vector<Building> result;
    for (auto it = buildings.begin(); it != buildings.end(); it++) {
        result.push_back(it->second);
    }
    return result;
}
