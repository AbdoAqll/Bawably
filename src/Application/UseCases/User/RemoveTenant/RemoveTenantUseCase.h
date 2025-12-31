#ifndef FINALPROJECT_REMOVETENANTUSECASE_H
#define FINALPROJECT_REMOVETENANTUSECASE_H

#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/User/Interfaces/IUserRepository.h"
#include <memory>

struct RemoveTenantParams {
    int id;
};

class RemoveTenantUseCase : public IUseCase {
private:
    shared_ptr<IUserRepository> userRepository;

public:
    RemoveTenantUseCase(shared_ptr<IUserRepository> userRepo);
    any execute(const any &params = {}) override;
};

#endif //FINALPROJECT_REMOVETENANTUSECASE_H