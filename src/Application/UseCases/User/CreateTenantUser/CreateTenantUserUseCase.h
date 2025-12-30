#ifndef CREATETENANTUSERUSECASE_H
#define CREATETENANTUSERUSECASE_H

#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/User/Interfaces/IUserRepository.h"
#include <memory>

using namespace std;

struct CreateTenantUserParams {
    int tenantId;
    string username;
    string password;
    int apartmentId;
    int buildingId;
};

class CreateTenantUserUseCase : public IUseCase {
private:
    shared_ptr<IUserRepository> userRepository;

public:
    CreateTenantUserUseCase(shared_ptr<IUserRepository> userRepo);
    any execute(const any &params = {}) override;
};

#endif // CREATETENANTUSERUSECASE_H
