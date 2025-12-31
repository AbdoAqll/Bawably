#include "InMemoryApartmentRepository.h"

#include <Apartment/Exceptions/ApartmentNotExistException.h>

InMemoryApartmentRepository::InMemoryApartmentRepository() {
    string apt1 = "101";
    Apartment a1(1, apt1);
    apartments.insert({ a1.getId(), a1 });

    string apt2 = "102";
    Apartment a2(1, apt2);
    apartments.insert({ a2.getId(), a2 });

    string apt3 = "201";
    Apartment a3(1, apt3);

    apartments.insert({ a3.getId(), a3 });

    string apt4 = "202";
    Apartment a4(1, apt4);
    apartments.insert({ a4.getId(), a4 });

    string apt5 = "A1";
    Apartment a5(2, apt5);
    apartments.insert({ a5.getId(), a5 });

    string apt6 = "A2";
    Apartment a6(2, apt6);
    apartments.insert({ a6.getId(), a6 });

    string apt7 = "B1";
    Apartment a7(2, apt7);
    apartments.insert({ a7.getId(), a7 });

    string apt8 = "1A";
    Apartment a8(3, apt8);
    apartments.insert({ a8.getId(), a8 });

    string apt9 = "2A";
    Apartment a9(3, apt9);
    apartments.insert({ a9.getId(), a9 });

    string apt10 = "3A";
    Apartment a10(3, apt10);
    apartments.insert({ a10.getId(), a10 });
}

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






