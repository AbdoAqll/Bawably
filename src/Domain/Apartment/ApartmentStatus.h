#include <ostream>

enum class ApartmentStatus
{
    Vacant,
    Rented
};

std::ostream& operator<<(std::ostream& os, ApartmentStatus status);
