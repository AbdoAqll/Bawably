#ifndef LOGINUSECASE_H
#define LOGINUSECASE_H

#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/User/Interfaces/IUserRepository.h"
#include <memory>

using namespace std;

struct LoginParams {
    string username;
    string password;
};

class LoginUseCase : public IUseCase {
private:
    shared_ptr<IUserRepository> userRepository;

public:
    explicit LoginUseCase(shared_ptr<IUserRepository> repo);
    any execute(const any& params = {}) override;
    
};

#endif // LOGINUSECASE_H
