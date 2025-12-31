#include "Owner.h"

Owner::Owner(const string& username, const string& password)
    : User(username, password, UserRole::OWNER) {
}
