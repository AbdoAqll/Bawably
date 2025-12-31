#ifndef INVALIDMONTHEXCEPTION_H
#define INVALIDMONTHEXCEPTION_H

#include "./Shared/DomainException.h"

class InvalidMonthException : public DomainException {
public:
    explicit InvalidMonthException(int month);
};

#endif //INVALIDMONTHEXCEPTION_H
