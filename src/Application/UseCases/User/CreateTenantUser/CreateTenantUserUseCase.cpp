#include "CreateTenantUserUseCase.h"
#include "Domain/User/TenantUser.h"
#include "Domain/User/Exceptions/TenantAlreadyExistsException.h"
#include "Domain/User/Exceptions/UsernameAlreadyTakenException.h"
#include "Domain/User/Exceptions/TenantUserCreationFailedException.h"

CreateTenantUserUseCase::CreateTenantUserUseCase(
    shared_ptr<IUserRepository> userRepo)
    : userRepository(userRepo) {
    UseCaseName = "CreateTenantUser";
}

any CreateTenantUserUseCase::execute(const any& params) {
    auto createParams = any_cast<CreateTenantUserParams>(params);

    if (userRepository->tenantUserExists(createParams.natId)) {
        throw TenantAlreadyExistsException(createParams.natId);
    }

    if (userRepository->findByUsername(createParams.username) != nullptr) {
        throw UsernameAlreadyTakenException(createParams.username);
    }


    TenantUser tenantUser(createParams.username, createParams.password, createParams.fullName, createParams.natId, createParams.phoneNum);

    if (!userRepository->saveTenantUser(tenantUser)) {
        throw TenantUserCreationFailedException();
    }
    return tenantUser.getUserId();
}
