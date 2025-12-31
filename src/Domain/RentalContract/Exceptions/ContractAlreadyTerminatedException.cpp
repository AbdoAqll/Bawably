#include "ContractAlreadyTerminatedException.h"

ContractAlreadyTerminatedException::ContractAlreadyTerminatedException(int contractId)
    : DomainException("Contract with ID " + std::to_string(contractId) + " is already terminated") {
}
