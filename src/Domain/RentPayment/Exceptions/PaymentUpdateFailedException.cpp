#include "PaymentUpdateFailedException.h"

PaymentUpdateFailedException::PaymentUpdateFailedException(int paymentId)
    : DomainException("Failed to update rent payment with ID " + std::to_string(paymentId)) {
}
