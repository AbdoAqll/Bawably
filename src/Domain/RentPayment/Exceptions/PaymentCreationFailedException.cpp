#include "PaymentCreationFailedException.h"

PaymentCreationFailedException::PaymentCreationFailedException()
    : DomainException("Failed to create rent payment") {
}
