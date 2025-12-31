#include "CreateTenantUserUseCase.h"
#include "Domain/User/TenantUser.h"
#include <stdexcept>

CreateTenantUserUseCase::CreateTenantUserUseCase(
    shared_ptr<IUserRepository> userRepo)
    : userRepository(userRepo) {
    UseCaseName = "CreateTenantUser";
}

any CreateTenantUserUseCase::execute(const any& params) {
    auto createParams = any_cast<CreateTenantUserParams>(params);

    if (userRepository->tenantUserExists(createParams.natId)) {
        throw runtime_error("Tenant with NationalId " + createParams.natId + " already exists.");
    }

    if (userRepository->findByUsername(createParams.username) != nullptr) {
        throw runtime_error("Username '" + createParams.username + "' is already taken");
    }


    TenantUser tenantUser(createParams.username,createParams.password,createParams.fullName, createParams.natId, createParams.phoneNum);

    if (!userRepository->saveTenantUser(tenantUser)) {
        throw runtime_error("Failed to create tenant user account");
    }
    return tenantUser.getUserId();
}
