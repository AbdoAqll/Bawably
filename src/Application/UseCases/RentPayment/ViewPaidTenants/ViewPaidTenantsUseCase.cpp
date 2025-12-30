#include "ViewPaidTenantsUseCase.h"
#include "Domain/Shared/DomainException.h"

ViewPaidTenantsUseCase::ViewPaidTenantsUseCase(
    const shared_ptr<IRentPaymentRepository>& rentPaymentRepository,
    const shared_ptr<IRentalContractRepository>& rentalContractRepository,
    const shared_ptr<IUserRepository>& userRepository) {
    _rentPaymentRepository = rentPaymentRepository;
    _rentalContractRepository = rentalContractRepository;
    _userRepository = userRepository;
    UseCaseName = "ViewPaidTenants";
}

any ViewPaidTenantsUseCase::execute(const any& params) {
    auto args = any_cast<ViewPaidTenantsParams>(params);

    // Validate month (1-12)
    if (args.month < 1 || args.month > 12) {
        throw DomainException("Invalid month. Must be between 1 and 12");
    }

    // Validate year
    if (args.year < 2000 || args.year > 2100) {
        throw DomainException("Invalid year. Must be between 2000 and 2100");
    }

    // Get all payments with Paid status for the specified month/year
    auto paidPayments = _rentPaymentRepository->findByStatus(PaymentStatus::Paid, args.month, args.year);

    vector<PaidTenantInfo> paidTenants;

    for (const auto& payment : paidPayments) {
        PaidTenantInfo info;
        info.tenantId = payment.getTenantId();
        info.contractId = payment.getContractId();
        info.amountPaid = payment.getAmountPaid();
        info.expectedAmount = payment.getExpectedAmount();
        info.paymentDate = payment.getPaymentDate();

        // Get contract details
        auto contract = _rentalContractRepository->findById(payment.getContractId());
        if (contract != nullptr) {
            info.apartmentId = contract->getApartmentId();
            info.buildingId = contract->getBuildingId();
        }
        else {
            info.apartmentId = 0;
            info.buildingId = 0;
        }

        // Get tenant name
        auto tenant = _userRepository->findTenantUserByTenantId(payment.getTenantId());
        if (tenant != nullptr) {
            info.tenantName = tenant->getUsername();
        }
        else {
            info.tenantName = "Unknown Tenant";
        }

        paidTenants.push_back(info);
    }

    return paidTenants;
}
