#include "ContractUpdateFailedException.h"

ContractUpdateFailedException::ContractUpdateFailedException(int contractId)
    : DomainException("Failed to update rental contract with ID " + std::to_string(contractId)) {
}
