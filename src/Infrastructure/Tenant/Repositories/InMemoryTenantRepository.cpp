#include "InMemoryTenantRepository.h"

InMemoryTenantRepository::InMemoryTenantRepository() {
    nextId = 1;
}

bool InMemoryTenantRepository::save(const Tenant& tenant) {
    int id = tenant.getTenantId();

    if (tenants.find(id) != tenants.end()) {
        return false;
    }

    tenants.insert({ id, tenant });
    return true;
}

Tenant* InMemoryTenantRepository::findById(int tenantId) {
    auto it = tenants.find(tenantId);
    if (it != tenants.end()) {
        return &(it->second);
    }
    return nullptr;
}

vector<Tenant> InMemoryTenantRepository::getAll() {
    vector<Tenant> allTenants;
    for (const auto& pair : tenants) {
        allTenants.push_back(pair.second);
    }
    return allTenants;
}

bool InMemoryTenantRepository::exists(int tenantId) {
    return tenants.find(tenantId) != tenants.end();
}

bool InMemoryTenantRepository::update(const Tenant& tenant) {
    int id = tenant.getTenantId();

    if (tenants.find(id) == tenants.end()) {
        return false;
    }

    tenants.at(id) = tenant;
    return true;
}
