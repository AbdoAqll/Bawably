#ifndef USER_REPOSITORY_H
#define USER_REPOSITORY_H

#include "Application/UseCases/User/Interfaces/IUserRepository.h"
#include "Domain/User/User.h"
#include <unordered_map>
#include <memory>

class UserRepository : public IUserRepository
{
private:
    std::unordered_map<int, User> users;

public:
    UserRepository() = default;
    ~UserRepository() = default;

    bool save(const User &user) override
    {
        users[user.getId()] = user;
        return true;
    }

    User findById(int id) override
    {
        if (users.find(id) != users.end())
        {
            return users[id];
        }
        return User();
    }

    bool exists(int id) override
    {
        return users.find(id) != users.end();
    }
};

#endif // USER_REPOSITORY_H
