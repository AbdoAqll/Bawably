#include "Apartment.h"

Apartment::Apartment(int id, int buildingId, string &number)
{
    apartmentId = id;
    buildingId = buildingId;
    apartmentNumber = number;
    status = ApartmentStatus::Vacant;
}

int Apartment::getId() const
{
    return apartmentId;
}

int Apartment::getBuildingId() const
{
    return buildingId;
}

string Apartment::getApartmentNumber() const
{
    return apartmentNumber;
}

ApartmentStatus Apartment::getStatus() const
{
    return status;
}

void Apartment::setStatus(ApartmentStatus newStatus)
{
    status = newStatus;
}