#ifndef PAYMENTRECORDEXISTSEXCEPTION_H
#define PAYMENTRECORDEXISTSEXCEPTION_H

#include <Shared/DomainException.h>

class PaymentRecordExistsException : public DomainException {
public:
    PaymentRecordExistsException(int contractId, int month, int year);
};

#endif //PAYMENTRECORDEXISTSEXCEPTION_H
