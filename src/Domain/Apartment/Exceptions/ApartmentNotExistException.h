#ifndef APARTMENTNOTEXISTEXCEPTION_H
#define APARTMENTNOTEXISTEXCEPTION_H
#include <Shared/DomainException.h>

class ApartmentNotExistException : public DomainException {
public:
    explicit ApartmentNotExistException(string apartmentNumber, int buildingId);
};
#endif //APARTMENTNOTEXISTEXCEPTION_H
