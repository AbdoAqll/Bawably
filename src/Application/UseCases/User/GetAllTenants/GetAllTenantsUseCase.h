
#ifndef FINALPROJECT_GETALLTENANTSUSECASE_H
#define FINALPROJECT_GETALLTENANTSUSECASE_H

#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/User/Interfaces/IUserRepository.h"
#include <memory>

class GetAllTenantsUseCase : public IUseCase {
private:
    shared_ptr<IUserRepository> userRepository;

public:
    explicit GetAllTenantsUseCase(shared_ptr<IUserRepository> userRepo);
    any execute(const any &params = {}) override;
};


#endif //FINALPROJECT_GETALLTENANTSUSECASE_H