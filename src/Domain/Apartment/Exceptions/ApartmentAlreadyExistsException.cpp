#include "ApartmentAlreadyExistsException.h"

ApartmentAlreadyExistsException::ApartmentAlreadyExistsException(string apartmentNumber, int buildingId)
    :DomainException("Building with Id: " + to_string(buildingId) + " already contains an apartment with Id: " + apartmentNumber) {}
