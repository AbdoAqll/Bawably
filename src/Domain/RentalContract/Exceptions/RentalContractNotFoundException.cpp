#include "RentalContractNotFoundException.h"

RentalContractNotFoundException::RentalContractNotFoundException(int contractId)
    : DomainException("Rental contract with ID " + std::to_string(contractId) + " not found") {
}
