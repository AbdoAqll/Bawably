#ifndef OWNER_H
#define OWNER_H

#include "User.h"

class Owner : public User {
public:
    Owner(const string& username, const string& password);
};

#endif // OWNER_H
