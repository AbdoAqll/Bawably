#ifndef INMEMORYTENANTREPOSITORY_H
#define INMEMORYTENANTREPOSITORY_H

#include "Application/UseCases/Tenant/Interfaces/ITenantRepository.h"
#include <map>
#include <vector>
using namespace std;

class InMemoryTenantRepository : public ITenantRepository {
private:
    map<int, Tenant> tenants;
    int nextId;

public:
    InMemoryTenantRepository();
    ~InMemoryTenantRepository() override = default;

    bool save(const Tenant &tenant) override;
    Tenant* findById(int tenantId) override;
    vector<Tenant> getAll() override;
    bool exists(int tenantId) override;
    bool update(const Tenant &tenant) override;
};

#endif //INMEMORYTENANTREPOSITORY_H
