#include "ViewPaidTenantsUseCase.h"
#include "Domain/RentPayment/Exceptions/InvalidMonthException.h"
#include "Domain/RentPayment/Exceptions/InvalidYearException.h"

ViewPaidTenantsUseCase::ViewPaidTenantsUseCase(
    const shared_ptr<IRentPaymentRepository>& rentPaymentRepository,
    const shared_ptr<IRentalContractRepository>& rentalContractRepository,
    const shared_ptr<IUserRepository>& userRepository,
    const shared_ptr<IApartmentRepository>& apartmentRepository) {
    _rentPaymentRepository = rentPaymentRepository;
    _rentalContractRepository = rentalContractRepository;
    _userRepository = userRepository;
    _apartmentRepository = apartmentRepository;
    UseCaseName = "ViewPaidTenants";
}

any ViewPaidTenantsUseCase::execute(const any& params) {
    auto args = any_cast<ViewPaidTenantsParams>(params);

    // Validate month (1-12)
    if (args.month < 1 || args.month > 12) {
        throw InvalidMonthException(args.month);
    }

    // Validate year
    if (args.year < 2000 || args.year > 2100) {
        throw InvalidYearException(args.year);
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
            // Get buildingId from apartment
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

        paidTenants.push_back(info);
    }

    return paidTenants;
}
