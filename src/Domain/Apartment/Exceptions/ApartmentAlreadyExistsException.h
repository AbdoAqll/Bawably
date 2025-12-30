#ifndef APARTMENTALREADYEXISTS_H
#define APARTMENTALREADYEXISTS_H
#include <Shared/DomainException.h>

class ApartmentAlreadyExistsException : public DomainException {
public:
    explicit ApartmentAlreadyExistsException(string apartmentNumber, int buildingId);
};
#endif //APARTMENTALREADYEXISTS_H
