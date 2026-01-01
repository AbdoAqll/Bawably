#ifndef INVALIDPAYMENTAMOUNTEXCEPTION_H
#define INVALIDPAYMENTAMOUNTEXCEPTION_H

#include <Shared/DomainException.h>

class InvalidPaymentAmountException : public DomainException {
public:
    explicit InvalidPaymentAmountException(double amount, bool mustBePositive = false);
};

#endif //INVALIDPAYMENTAMOUNTEXCEPTION_H
