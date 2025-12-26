#include "InMemoryApartmentRepository.h"

#include <Apartment/Exceptions/ApartmentNotExistException.h>

bool InMemoryApartmentRepository::save(const Apartment &apartment) {
    int id = apartment.getId();
    bool exists = false;
    for (const auto& pair : apartments) {
        if (pair.second.getApartmentNumber() == apartment.getApartmentNumber()) {
            exists = true;
            break;
        }
    }
    if (exists) {
        return false;
    }
    apartments.insert({id, apartment});
    return true;
}

vector<Apartment> InMemoryApartmentRepository::getAll(int buildingId) {
    vector<Apartment> result;
    for (const auto& pair : apartments) {
        const Apartment& apt = pair.second;
        if (apt.getBuildingId() == buildingId) {
            result.push_back(apt);
        }
    }
    return result;
}

Apartment InMemoryApartmentRepository::findById(int id, int buildingId) {
    if (exists(id, buildingId)) {
        return apartments.at(id);
    }
    throw ApartmentNotExistException(to_string(id), buildingId);
}

bool InMemoryApartmentRepository::exists(int id, int buildingId) {
    auto it = apartments.find(id);
    if (it != apartments.end() && it->second.getBuildingId() == buildingId) {
        return true;
    }
    return false;
}

int InMemoryApartmentRepository::getApartmentIdFromApartmentNumber(string apartmentNumber) {
    int apartmentId = -1;
    for (const auto& pair : apartments) {
        if (pair.second.getApartmentNumber() == apartmentNumber) {
            apartmentId = pair.second.getId();
            break;
        }
    }
    return apartmentId;
}






