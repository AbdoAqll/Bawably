#ifndef USER_H
#define USER_H

#include <string>

using namespace std;

enum class UserRole {
    OWNER,
    TENANT
};

class User {
protected:
    int userId;
    string username;
    string password;
    UserRole role;
    static int nextId;

public:
    User(const string& username, const string& password, UserRole role);
    virtual ~User() = default;

    int getUserId() const;
    string getUsername() const;
    string getPassword() const;
    UserRole getRole() const;

    bool validatePassword(const string& inputPassword) const;
};

#endif // USER_H
