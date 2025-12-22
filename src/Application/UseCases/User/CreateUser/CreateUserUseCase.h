#ifndef CREATE_USER_USE_CASE_H
#define CREATE_USER_USE_CASE_H

#include "Domain/User/User.h"
#include "Application/UseCases/User/Interfaces/IUserRepository.h"
#include <memory>

class CreateUserUseCase
{
private:
    std::shared_ptr<IUserRepository> userRepository;

public:
    CreateUserUseCase(std::shared_ptr<IUserRepository> repository)
        : userRepository(repository) {}

    bool execute(int id, const std::string &name, const std::string &email)
    {
        User user(id, name, email);
        return userRepository->save(user);
    }
};

#endif // CREATE_USER_USE_CASE_H
