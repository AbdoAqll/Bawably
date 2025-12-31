#include "TenantNotExistException.h"

TenantNotExistException::TenantNotExistException(int tenantId)
    : DomainException("Tenant with ID " + std::to_string(tenantId) + " does not exist") {
}
