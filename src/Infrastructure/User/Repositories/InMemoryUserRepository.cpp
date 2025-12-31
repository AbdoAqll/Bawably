#include "InMemoryUserRepository.h"

InMemoryUserRepository::InMemoryUserRepository() {
    owner = make_shared<Owner>("admin", "admin123");

    TenantUser defaultTenant("shoura","asd123",
                  "mahmoud Ahmed Shoura", "123456789", "0123456789");
    tenantUsers.insert({ defaultTenant.getUserId(), defaultTenant });
}

shared_ptr<User> InMemoryUserRepository::findByCredentials(const string& username, const string& password) {
    if (owner->getUsername() == username && owner->validatePassword(password)) {
        return owner;
    }

    for (auto& pair : tenantUsers) {
        if (pair.second.getUsername() == username && pair.second.validatePassword(password)) {
            return make_shared<TenantUser>(pair.second);
        }
    }

    return nullptr;
}

shared_ptr<User> InMemoryUserRepository::findByUsername(const string& username) {
    if (owner->getUsername() == username) {
        return owner;
    }

    for (auto& pair : tenantUsers) {
        if (pair.second.getUsername() == username) {
            return make_shared<TenantUser>(pair.second);
        }
    }

    return nullptr;
}

bool InMemoryUserRepository::saveTenantUser(const TenantUser& tenantUser) {
    if (tenantUserExists(tenantUser.getUserId())) {
        return false;
    }

    if (findByUsername(tenantUser.getUsername()) != nullptr) {
        return false;
    }

    tenantUsers.insert({ tenantUser.getUserId(), tenantUser });
    return true;
}

vector<TenantUser> InMemoryUserRepository::getAllTenantUsers() {
    vector<TenantUser> allUsers;
    for (const auto& pair : tenantUsers) {
        allUsers.push_back(pair.second);
    }
    return allUsers;
}

bool InMemoryUserRepository::tenantUserExists(int tenantId) {
    for (const auto& pair : tenantUsers) {
        if (pair.second.getUserId() == tenantId) {
            return true;
        }
    }
    return false;
}

bool InMemoryUserRepository::tenantUserExists(const string& ssn) {
    for (const auto& pair : tenantUsers) {
        if (pair.second.getNationalId() == ssn) {
            return true;
        }
    }
    return false;
}

bool InMemoryUserRepository::removeTenant(int tenantId) {     /// Added by Shoura
    for (const auto& pair : tenantUsers) {
        if (pair.second.getUserId() == tenantId) {
            tenantUsers.erase(pair.second.getUserId());
            return true;
        }
    }
    return false;
}


shared_ptr<TenantUser> InMemoryUserRepository::findTenantUserByTenantId(int tenantId) {
    auto it = tenantUsers.find(tenantId);
    if (it != tenantUsers.end()) {
        return make_shared<TenantUser>(it->second);
    }
    return nullptr;
}
