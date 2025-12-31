#ifndef PAYMENTUPDATEFAILEDEXCEPTION_H
#define PAYMENTUPDATEFAILEDEXCEPTION_H

#include "../../Shared/DomainException.h"

class PaymentUpdateFailedException : public DomainException {
public:
    explicit PaymentUpdateFailedException(int paymentId);
};

#endif //PAYMENTUPDATEFAILEDEXCEPTION_H
