#include "CreateTenantUserUseCase.h"
#include "Domain/User/TenantUser.h"
#include <stdexcept>

#include "User/Exceptions/TenantUserAlreadyExists.h"

CreateTenantUserUseCase::CreateTenantUserUseCase(
    shared_ptr<IUserRepository> userRepo)
    : userRepository(userRepo) {
    UseCaseName = "CreateTenantUser";
}

any CreateTenantUserUseCase::execute(const any& params) {
    CreateTenantUserParams args = any_cast<CreateTenantUserParams>(params);

    // Check if tenant exists
    if (userRepository->tenantUserExists(args.tenantId)) {
        throw TenantUserAlreadyExists(args.tenantId);
    }

    // Check if username is already taken
    if (userRepository->findByUsername(args.username) != nullptr) {
        throw TenantUserAlreadyExists(args.username);
    }

    TenantUser tenantUser(args.tenantId,args.username,args.password,args.fullName,
                          args.natId, args.phoneNum);

    return userRepository->saveTenantUser(tenantUser);
}
