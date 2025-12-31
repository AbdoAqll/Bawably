#include "InvalidPaymentAmountException.h"

InvalidPaymentAmountException::InvalidPaymentAmountException(double amount, bool mustBePositive)
    : DomainException(mustBePositive
        ? "Payment amount must be positive. Received: " + std::to_string(amount)
        : "Payment amount cannot be negative. Received: " + std::to_string(amount)) {
}
