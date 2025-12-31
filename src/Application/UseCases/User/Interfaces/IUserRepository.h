#ifndef IUSERREPOSITORY_H
#define IUSERREPOSITORY_H

#include "Domain/User/User.h"
#include "Domain/User/Owner.h"
#include "Domain/User/TenantUser.h"
#include <memory>
#include <vector>

using namespace std;

class IUserRepository {
public:
    virtual ~IUserRepository() = default;

    virtual shared_ptr<User> findByCredentials(const string& username, const string& password) = 0;
    virtual shared_ptr<User> findByUsername(const string& username) = 0;
    virtual bool saveTenantUser(const TenantUser& tenantUser) = 0;
    virtual vector<TenantUser> getAllTenantUsers() = 0;
    virtual bool tenantUserExists(int tenantId) = 0;
    virtual bool tenantUserExists(const string& ssn) = 0;
    virtual bool removeTenant(int tenantId) = 0;         /// Added by Shoura
    virtual shared_ptr<TenantUser> findTenantUserByTenantId(int tenantId) = 0;
};

#endif // IUSERREPOSITORY_H
