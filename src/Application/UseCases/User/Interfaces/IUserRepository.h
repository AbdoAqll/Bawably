#ifndef IUSER_REPOSITORY_H
#define IUSER_REPOSITORY_H

#include "Domain/User/User.h"

class IUserRepository
{
public:
    virtual ~IUserRepository() = default;

    virtual bool save(const User &user) = 0;
    virtual User findById(int id) = 0;
    virtual bool exists(int id) = 0;
};

#endif // IUSER_REPOSITORY_H
