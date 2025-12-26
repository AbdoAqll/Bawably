#include "ApartmentStatus.h"

std::ostream& operator<<(std::ostream& os, ApartmentStatus status) {
    switch (status) {
        case ApartmentStatus::Vacant:
            os << "Vacant";
            break;
        case ApartmentStatus::Rented:
            os << "Rented";
            break;
        default:
            os << "Unknown";
            break;
    }
    return os;
}