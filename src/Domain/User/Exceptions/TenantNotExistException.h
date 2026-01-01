#ifndef TENANTNOTEXISTEXCEPTION_H
#define TENANTNOTEXISTEXCEPTION_H

#include <Shared/DomainException.h>

class TenantNotExistException : public DomainException {
public:
    explicit TenantNotExistException(int tenantId);
};

#endif //TENANTNOTEXISTEXCEPTION_H
