#include <Shared/DomainException.h>
#ifndef FINALPROJECT_TENANTUSERALREADYEXISTS_H
#define FINALPROJECT_TENANTUSERALREADYEXISTS_H

class TenantUserAlreadyExists : public DomainException {
public:
    explicit TenantUserAlreadyExists(string tenantUserName);
    explicit TenantUserAlreadyExists(int tenantId);
};

#endif //FINALPROJECT_TENANTUSERALREADYEXISTS_H