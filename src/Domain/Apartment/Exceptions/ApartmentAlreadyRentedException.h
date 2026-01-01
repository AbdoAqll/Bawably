#ifndef APARTMENTALREADYRENTEDEXCEPTION_H
#define APARTMENTALREADYRENTEDEXCEPTION_H

#include <Shared/DomainException.h>

class ApartmentAlreadyRentedException : public DomainException {
public:
    explicit ApartmentAlreadyRentedException(int apartmentId);
};

#endif //APARTMENTALREADYRENTEDEXCEPTION_H
