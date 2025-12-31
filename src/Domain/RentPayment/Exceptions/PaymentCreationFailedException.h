#ifndef PAYMENTCREATIONFAILEDEXCEPTION_H
#define PAYMENTCREATIONFAILEDEXCEPTION_H

#include "../../Shared/DomainException.h"

class PaymentCreationFailedException : public DomainException {
public:
    PaymentCreationFailedException();
};

#endif //PAYMENTCREATIONFAILEDEXCEPTION_H
