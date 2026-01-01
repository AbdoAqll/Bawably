#ifndef INVALIDEXPENSEAMOUNTEXCEPTION_H
#define INVALIDEXPENSEAMOUNTEXCEPTION_H

#include <Shared/DomainException.h>

class InvalidExpenseAmountException : public DomainException {
public:
    explicit InvalidExpenseAmountException(double amount);
};

#endif //INVALIDEXPENSEAMOUNTEXCEPTION_H