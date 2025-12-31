#include "PaymentRecordExistsException.h"

PaymentRecordExistsException::PaymentRecordExistsException(int contractId, int month, int year)
    : DomainException("A payment record already exists for contract ID " + std::to_string(contractId) +
        " in " + std::to_string(month) + "/" + std::to_string(year) + ". Use 'Add Partial Payment' to update.") {
}
