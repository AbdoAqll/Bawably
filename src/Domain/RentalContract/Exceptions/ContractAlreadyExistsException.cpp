#include "ContractAlreadyExistsException.h"

ContractAlreadyExistsException::ContractAlreadyExistsException(int apartmentId, int tenantId)
    : DomainException("Active rental contract already exists for apartment ID " +
        std::to_string(apartmentId) + " and tenant ID " + std::to_string(tenantId)) {
}
