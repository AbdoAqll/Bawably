#ifndef INMEMORYUSERREPOSITORY_H
#define INMEMORYUSERREPOSITORY_H

#include "Application/UseCases/User/Interfaces/IUserRepository.h"
#include <map>
#include <vector>

using namespace std;

class InMemoryUserRepository : public IUserRepository {
private:
    shared_ptr<Owner> owner;
    map<int, TenantUser> tenantUsers;
public:
    InMemoryUserRepository();
    ~InMemoryUserRepository() override = default;

    shared_ptr<User> findByCredentials(const string& username, const string& password) override;
    shared_ptr<User> findByUsername(const string& username) override;
    bool saveTenantUser(const TenantUser& tenantUser) override;
    vector<TenantUser> getAllTenantUsers() override;
    bool tenantUserExists(int tenantId) override;
    bool tenantUserExists(const string& ssn) override;
    bool removeTenant(int tenantId) override;         /// Added by Shoura
    shared_ptr<TenantUser> findTenantUserByTenantId(int tenantId) override;
};

#endif // INMEMORYUSERREPOSITORY_H
