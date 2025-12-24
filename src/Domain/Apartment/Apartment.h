#include "ApartmentStatus.h"
#include <string>

using namespace std;

class Apartment
{
private:
    int apartmentId;
    int buildingId;
    string apartmentNumber;
    ApartmentStatus status;

public:
    Apartment(int id, int buildingId, string &number);
    int getId() const;
    int getBuildingId() const;
    string getApartmentNumber() const;
    ApartmentStatus getStatus() const;

    void setStatus(ApartmentStatus newStatus);
};