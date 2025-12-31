#include "ApartmentAlreadyRentedException.h"

ApartmentAlreadyRentedException::ApartmentAlreadyRentedException(int apartmentId)
    : DomainException("Apartment with ID " + std::to_string(apartmentId) + " is already rented") {
}
