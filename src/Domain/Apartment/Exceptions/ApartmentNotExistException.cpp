#include "ApartmentNotExistException.h"

ApartmentNotExistException::ApartmentNotExistException(string apartmentNumber, int buildingId)
    : DomainException("Building with Id: " + to_string(buildingId) + " doesn't contain apartment with number: " + apartmentNumber) {
}

ApartmentNotExistException::ApartmentNotExistException(string apartmentId)
    : DomainException("Apartment with Id: " + apartmentId + " does not exist.") {
}