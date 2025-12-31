#include "ViewUnpaidOrPartialTenantsUseCase.h"
#include "Domain/Shared/InvalidMonthException.h"
#include "Domain/Shared/InvalidYearException.h"

ViewUnpaidOrPartialTenantsUseCase::ViewUnpaidOrPartialTenantsUseCase(
    const shared_ptr<IRentPaymentRepository>& rentPaymentRepository,
    const shared_ptr<IRentalContractRepository>& rentalContractRepository,
    const shared_ptr<IUserRepository>& userRepository,
    const shared_ptr<IApartmentRepository>& apartmentRepository) {
    _rentPaymentRepository = rentPaymentRepository;
    _rentalContractRepository = rentalContractRepository;
    _userRepository = userRepository;
    _apartmentRepository = apartmentRepository;
    UseCaseName = "ViewUnpaidOrPartialTenants";
}

any ViewUnpaidOrPartialTenantsUseCase::execute(const any& params) {
    auto args = any_cast<ViewUnpaidOrPartialTenantsParams>(params);

    // Validate month (1-12)
    if (args.month < 1 || args.month > 12) {
        throw InvalidMonthException(args.month);
    }

    // Validate year
    if (args.year < 2000 || args.year > 2100) {
        throw InvalidYearException(args.year);
    }

    vector<UnpaidOrPartialTenantInfo> results;

    // Get partial payments for the specified month/year
    auto partialPayments = _rentPaymentRepository->findByStatus(PaymentStatus::Partial, args.month, args.year);

    for (const auto& payment : partialPayments) {
        UnpaidOrPartialTenantInfo info;
        info.tenantId = payment.getTenantId();
        info.contractId = payment.getContractId();
        info.amountPaid = payment.getAmountPaid();
        info.expectedAmount = payment.getExpectedAmount();
        info.remainingAmount = payment.getRemainingAmount();
        info.status = payment.getStatus();
        info.paymentDate = payment.getPaymentDate();

        auto contract = _rentalContractRepository->findById(payment.getContractId());
        if (contract != nullptr) {
            info.apartmentId = contract->getApartmentId();
        }
        else {
            info.apartmentId = 0;
        }

        auto tenant = _userRepository->findTenantUserByTenantId(payment.getTenantId());
        if (tenant != nullptr) {
            info.tenantName = tenant->getUsername();
        }
        else {
            info.tenantName = "Unknown Tenant";
        }

        results.push_back(info);
    }

    // Get unpaid payments for the specified month/year
    auto unpaidPayments = _rentPaymentRepository->findByStatus(PaymentStatus::Unpaid, args.month, args.year);

    for (const auto& payment : unpaidPayments) {
        UnpaidOrPartialTenantInfo info;
        info.tenantId = payment.getTenantId();
        info.contractId = payment.getContractId();
        info.amountPaid = payment.getAmountPaid();
        info.expectedAmount = payment.getExpectedAmount();
        info.remainingAmount = payment.getRemainingAmount();
        info.status = payment.getStatus();
        info.paymentDate = payment.getPaymentDate();

        auto contract = _rentalContractRepository->findById(payment.getContractId());
        if (contract != nullptr) {
            info.apartmentId = contract->getApartmentId();
            try {
                auto apartment = _apartmentRepository->findById(contract->getApartmentId());
                info.buildingId = apartment.getBuildingId();
            }
            catch (...) {
                info.buildingId = 0;
            }
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

        results.push_back(info);
    }

    // Also include active contracts that have no payment record for this month (completely unpaid)
    auto activeContracts = _rentalContractRepository->getActiveContracts();

    for (const auto& contract : activeContracts) {
        // Check if this contract already has a payment record for this month
        if (!_rentPaymentRepository->existsForContractAndMonth(contract.getContractId(), args.month, args.year)) {
            UnpaidOrPartialTenantInfo info;
            info.tenantId = contract.getTenantId();
            info.contractId = contract.getContractId();
            info.apartmentId = contract.getApartmentId();
            // Get buildingId from apartment
            try {
                auto apartment = _apartmentRepository->findById(contract.getApartmentId());
                info.buildingId = apartment.getBuildingId();
            }
            catch (...) {
                info.buildingId = 0;
            }
            info.amountPaid = 0.0;
            info.expectedAmount = contract.getMonthlyRent();
            info.remainingAmount = contract.getMonthlyRent();
            info.status = PaymentStatus::Unpaid;
            info.paymentDate = "";

            // Get tenant name
            auto tenant = _userRepository->findTenantUserByTenantId(contract.getTenantId());
            if (tenant != nullptr) {
                info.tenantName = tenant->getUsername();
            }
            else {
                info.tenantName = "Unknown Tenant";
            }

            results.push_back(info);
        }
    }

    return results;
}
