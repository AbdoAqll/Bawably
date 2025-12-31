#include "TenantAlreadyExistsException.h"

TenantAlreadyExistsException::TenantAlreadyExistsException(const std::string& nationalId)
    : DomainException("Tenant with NationalId " + nationalId + " already exists") {
}
