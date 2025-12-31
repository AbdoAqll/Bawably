#ifndef CREATETENANTUSERUSECASE_H
#define CREATETENANTUSERUSECASE_H

#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/User/Interfaces/IUserRepository.h"
#include <memory>

using namespace std;

struct CreateTenantUserParams {
    string username;
    string password;
    string phoneNum;
    string natId;
    string fullName;
};

class CreateTenantUserUseCase : public IUseCase {
private:
    shared_ptr<IUserRepository> userRepository;

public:
    explicit CreateTenantUserUseCase(shared_ptr<IUserRepository> userRepo);
    any execute(const any &params = {}) override;
};

#endif // CREATETENANTUSERUSECASE_H
