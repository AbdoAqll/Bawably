#include "ContractCreationFailedException.h"

ContractCreationFailedException::ContractCreationFailedException()
    : DomainException("Failed to create rental contract") {
}
