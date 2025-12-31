#include "RemoveTenantUseCase.h"
#include <memory>
using namespace std;
#include "../Interfaces/IUserRepository.h"


RemoveTenantUseCase::RemoveTenantUseCase(shared_ptr<IUserRepository> userRepo)
    : userRepository(userRepo) {
    UseCaseName = "RemoveTenant";
}

any RemoveTenantUseCase::execute(const any& params) {
    auto obj = any_cast<RemoveTenantParams>(params);
    return userRepository->removeTenant(obj.id);
}