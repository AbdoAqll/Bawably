#include <Shared/DomainException.h>
#ifndef FINALPROJECT_TENANTUSERNOTFOUND_H
#define FINALPROJECT_TENANTUSERNOTFOUND_H

class TenantUserNotFound : public DomainException {
public:
    explicit TenantUserNotFound(int tenantId);
};

#endif //FINALPROJECT_TENANTUSERNOTFOUND_H