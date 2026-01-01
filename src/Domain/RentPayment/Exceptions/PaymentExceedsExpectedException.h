#ifndef PAYMENTEXCEEDSEXPECTEDEXCEPTION_H
#define PAYMENTEXCEEDSEXPECTEDEXCEPTION_H

#include <Shared/DomainException.h>

class PaymentExceedsExpectedException : public DomainException {
public:
    PaymentExceedsExpectedException(double totalAmount, double expectedAmount, double remainingAmount);
};

#endif //PAYMENTEXCEEDSEXPECTEDEXCEPTION_H
