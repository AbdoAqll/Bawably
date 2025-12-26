#include "Apartment.h"

int Apartment::nextId = 0;
Apartment::Apartment(int buildingId, string &number)
{
    this->apartmentId = ++nextId;
    this->buildingId = buildingId;
    this->apartmentNumber = number;
    this->status = ApartmentStatus::Vacant;
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