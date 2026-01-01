#ifndef TENANTUSERCREATIONFAILEDEXCEPTION_H
#define TENANTUSERCREATIONFAILEDEXCEPTION_H

#include <Shared/DomainException.h>

class TenantUserCreationFailedException : public DomainException {
public:
    TenantUserCreationFailedException();
};

#endif //TENANTUSERCREATIONFAILEDEXCEPTION_H
