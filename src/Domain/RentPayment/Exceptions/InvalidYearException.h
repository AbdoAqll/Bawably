#ifndef INVALIDYEAREXCEPTION_H
#define INVALIDYEAREXCEPTION_H

#include "../../Shared/DomainException.h"

class InvalidYearException : public DomainException {
public:
    explicit InvalidYearException(int year);
};

#endif //INVALIDYEAREXCEPTION_H
