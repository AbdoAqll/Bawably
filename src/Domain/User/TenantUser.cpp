#include "TenantUser.h"
using namespace std;

TenantUser::TenantUser(int userId, const string &username, const string &password, const string &name, const string &natlId, const string &phoneNum)
    : User (userId, username, password, UserRole::TENANT) , fullName(name), nationalId(natlId), phoneNumber(phoneNum)
{

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


void TenantUser::setFullName(const string& _fullname) {
    fullName = _fullname;
}
void TenantUser::setNationalId(const string& _nationalId) {
    nationalId = _nationalId;
}
void TenantUser::setPhoneNumber(const string& _phoneNumber) {
    phoneNumber = _phoneNumber;
}
