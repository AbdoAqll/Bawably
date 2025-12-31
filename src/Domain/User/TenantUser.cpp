#include "TenantUser.h"
using namespace std;

TenantUser::TenantUser(const string &username, const string &password, const string &name, const string &natlId, const string &phoneNum)
    : User (username, password, UserRole::TENANT)
{
    fullName = name;
    nationalId = natlId;
    phoneNumber = phoneNum;
}


int TenantUser::getUserId() const {
    return userId;
}
string TenantUser::getUserName() const {
    return username;
}
string TenantUser::getPassword() const {
    return password;
}
string TenantUser::getFullName() const {
    return fullName;
}
string TenantUser::getNationalId() const {
    return nationalId;
}
string TenantUser::getPhoneNumber() const {
    return phoneNumber;
}


void TenantUser::setUserId(int _userId) {
    userId = _userId;
}
void TenantUser::setUserName(const string& _userName) {
    username = _userName;
}
void TenantUser::setPassword(const string& _password) {
    password = _password;
}
void TenantUser::setFullName(const string& _fullname) {
    fullName = _fullname;
}
void TenantUser::setNationalId(const string& _nationalId) {
    nationalId = _nationalId;
}
void TenantUser::setPhoneNumber(const string& _phoneNumber) {
    phoneNumber = _phoneNumber;
}
