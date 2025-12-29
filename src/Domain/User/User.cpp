#include "User.h"

User::User(int id, const string& username, const string& password, UserRole role)
    : userId(id), username(username), password(password), role(role) {
}

int User::getUserId() const {
    return userId;
}

string User::getUsername() const {
    return username;
}

string User::getPassword() const {
    return password;
}

UserRole User::getRole() const {
    return role;
}

bool User::validatePassword(const string& inputPassword) const {
    return password == inputPassword;
}
