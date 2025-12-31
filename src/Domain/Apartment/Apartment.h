#include "ApartmentStatus.h"
#include <string>

using namespace std;

class Apartment {
private:
    int apartmentId;
    int buildingId;
    string apartmentNumber;
    ApartmentStatus status;
    static int nextId;

public:
    Apartment() = default;
    Apartment(int buildingId, string& number);
    int getId() const;
    int getBuildingId() const;
    string getApartmentNumber() const;
    ApartmentStatus getStatus() const;

    void setStatus(ApartmentStatus newStatus);
};