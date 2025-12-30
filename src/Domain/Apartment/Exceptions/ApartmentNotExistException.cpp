#include "ApartmentNotExistException.h"

ApartmentNotExistException::ApartmentNotExistException(string apartmentNumber, int buildingId)
: DomainException("Building with Id: " + to_string(buildingId) + " doesn't contain apartment with number: " + apartmentNumber) {}
