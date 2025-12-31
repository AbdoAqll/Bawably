#include "BuildingRepository.h"
#include "Domain/Building/Exceptions/BuildingNotExistException.h"
#include <string>

BuildingRepository::BuildingRepository() {
    // Add default buildings
    string name1 = "Sunset Apartments";
    string addr1 = "123 Main Street, Downtown";
    Building building1(name1, addr1);
    buildings.insert({ building1.getId(), building1 });

    string name2 = "Green Valley Complex";
    string addr2 = "456 Park Avenue, Westside";
    Building building2(name2, addr2);
    buildings.insert({ building2.getId(), building2 });

    string name3 = "Royal Heights";
    string addr3 = "789 King Road, Eastside";
    Building building3(name3, addr3);
    buildings.insert({ building3.getId(), building3 });
}

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
