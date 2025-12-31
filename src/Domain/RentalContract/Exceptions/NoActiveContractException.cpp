#include "NoActiveContractException.h"

NoActiveContractException::NoActiveContractException(int tenantId)
    : DomainException("No active rental contract found for tenant ID " + std::to_string(tenantId)) {
}
