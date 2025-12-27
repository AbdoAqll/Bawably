#ifndef ITENANTREPOSITORY_H
#define ITENANTREPOSITORY_H

#include "Domain/Tenant/Tenant.h"
#include <vector>
#include <memory>
using namespace std;

class ITenantRepository {
public:
    virtual ~ITenantRepository() = default;

    virtual bool save(const Tenant &tenant) = 0;
    virtual Tenant* findById(int tenantId) = 0;
    virtual vector<Tenant> getAll() = 0;
    virtual bool exists(int tenantId) = 0;
    virtual bool update(const Tenant &tenant) = 0;
};

#endif //ITENANTREPOSITORY_H
