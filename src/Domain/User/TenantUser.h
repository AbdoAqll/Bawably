#ifndef TENANT_USER_H
#define TENANT_USER_H

#include "User.h"

class TenantUser : public User {
private:
    std::string fullName;
    std::string nationalId;
    std::string phoneNumber;

public:
    TenantUser(int userId, const string& username, const string& password,
        const string& fullName, const string& nationalId, const string& phoneNumber);

    string getFullName() const;
    string getNationalId() const;
    string getPhoneNumber() const;

    void setFullName(const string& fullname);
    void setNationalId(const string& nationalId);
    void setPhoneNumber(const string& phoneNumber);
};

#endif // TENANT_USER_H
