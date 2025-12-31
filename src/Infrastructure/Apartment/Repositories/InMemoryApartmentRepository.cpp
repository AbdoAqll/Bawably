#include "InMemoryApartmentRepository.h"

#include <Apartment/Exceptions/ApartmentNotExistException.h>

bool InMemoryApartmentRepository::save(const Apartment& apartment) {
    int id = apartment.getId();

    // Check if apartment with this ID already exists
    auto it = apartments.find(id);
    if (it != apartments.end()) {
        // Update existing apartment
        it->second = apartment;
        return true;
    }

    // Check if apartment with same number and building already exists (for new apartments)
    for (const auto& pair : apartments) {
        if (pair.second.getApartmentNumber() == apartment.getApartmentNumber()
            && pair.second.getBuildingId() == apartment.getBuildingId()) {
            return false;  // Can't add duplicate apartment
        }
    }

    // Add new apartment
    apartments.insert({ id, apartment });
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

Apartment InMemoryApartmentRepository::findById(int id) {
    auto it = apartments.find(id);
    if (it != apartments.end()) {
        return it->second;
    }
    throw ApartmentNotExistException(to_string(id));
}

bool InMemoryApartmentRepository::exists(int id, int buildingId) {
    auto it = apartments.find(id);
    if (it != apartments.end() && it->second.getBuildingId() == buildingId) {
        return true;
    }
    return false;
}

int InMemoryApartmentRepository::getApartmentIdFromApartmentNumber(string apartmentNumber, int buildingId) {
    int apartmentId = -1;
    for (const auto& pair : apartments) {
        if (pair.second.getApartmentNumber() == apartmentNumber
            && pair.second.getBuildingId() == buildingId) {
            apartmentId = pair.second.getId();
            break;
        }
    }
    return apartmentId;
}






