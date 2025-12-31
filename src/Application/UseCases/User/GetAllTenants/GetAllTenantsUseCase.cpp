
#include <memory>
using namespace std;
#include "GetAllTenantsUseCase.h"
#include "../Interfaces/IUserRepository.h"


GetAllTenantsUseCase::GetAllTenantsUseCase(shared_ptr<IUserRepository> userRepo)
    : userRepository(userRepo) {
    UseCaseName = "GetAllTenants";
}

any GetAllTenantsUseCase::execute(const any& params) {
    vector<TenantUser> tenants = userRepository->getAllTenantUsers();
    return tenants;
}