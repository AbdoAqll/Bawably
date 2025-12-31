#include "TenantUserCreationFailedException.h"

TenantUserCreationFailedException::TenantUserCreationFailedException()
    : DomainException("Failed to create tenant user account") {
}
