#include "Owner.h"

Owner::Owner(int id, const string& username, const string& password)
    : User(id, username, password, UserRole::OWNER) {
}
