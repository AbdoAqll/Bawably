#include "GetRentalContractByTenantIdUseCase.h"
#include "Domain/User/Exceptions/TenantNotExistException.h"
#include "Domain/RentalContract/Exceptions/NoActiveContractException.h"

GetRentalContractByTenantIdUseCase::GetRentalContractByTenantIdUseCase(
    const shared_ptr<IRentalContractRepository>& rentalContractRepository,
    const shared_ptr<IUserRepository>& userRepository) {
    _rentalContractRepository = rentalContractRepository;
    _userRepository = userRepository;
    UseCaseName = "GetRentalContractByTenantId";
}

any GetRentalContractByTenantIdUseCase::execute(const any& params) {
    int tenantId = any_cast<int>(params);

    if (!_userRepository->tenantUserExists(tenantId)) {
        throw TenantNotExistException(tenantId);
    }

    RentalContract* contract = _rentalContractRepository->findActiveByTenant(tenantId);

    if (contract == nullptr) {
        throw NoActiveContractException(tenantId);
    }

    return *contract;
}
