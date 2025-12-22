#ifndef DELETE_USER_USE_CASE_H
#define DELETE_USER_USE_CASE_H

#include "Application/UseCases/User/Interfaces/IUserRepository.h"
#include <memory>

class DeleteUserUseCase
{
private:
    std::shared_ptr<IUserRepository> userRepository;

public:
    DeleteUserUseCase(std::shared_ptr<IUserRepository> repository)
        : userRepository(repository) {}

    bool execute(int id)
    {
        if (userRepository->exists(id))
        {
            // In a real implementation, you would call a delete method
            // For now, we just return true if user exists
            return true;
        }
        return false;
    }
};

#endif // DELETE_USER_USE_CASE_H
