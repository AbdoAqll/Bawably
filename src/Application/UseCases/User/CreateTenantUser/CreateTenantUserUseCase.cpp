#include "CreateTenantUserUseCase.h"
#include "Domain/User/TenantUser.h"
#include <stdexcept>

CreateTenantUserUseCase::CreateTenantUserUseCase(
    shared_ptr<IUserRepository> userRepo)
    : userRepository(userRepo) {
    UseCaseName = "CreateTenantUser";
}

any CreateTenantUserUseCase::execute(const any& params) {
    CreateTenantUserParams createParams = any_cast<CreateTenantUserParams>(params);

    // Check if tenant exists
    if (!userRepository->tenantUserExists(createParams.tenantId)) {
        throw runtime_error("Tenant with ID " + to_string(createParams.tenantId) + " does not exist");
    }

    // Check if username is already taken
    if (userRepository->findByUsername(createParams.username) != nullptr) {
        throw runtime_error("Username '" + createParams.username + "' is already taken");
    }

    // Generate user ID (using tenantId + 100 as a simple ID scheme)
    int userId = createParams.tenantId + 100;

    TenantUser tenantUser(userId, createParams.username, createParams.password,
        createParams.tenantId, createParams.apartmentId, createParams.buildingId);

    if (!userRepository->saveTenantUser(tenantUser)) {
        throw runtime_error("Failed to create tenant user account");
    }

    return userId;
}
