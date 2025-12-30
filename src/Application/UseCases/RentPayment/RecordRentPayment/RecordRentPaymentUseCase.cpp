#include "RecordRentPaymentUseCase.h"
#include "Domain/Shared/DomainException.h"

RecordRentPaymentUseCase::RecordRentPaymentUseCase(
    const shared_ptr<IRentPaymentRepository>& rentPaymentRepository,
    const shared_ptr<IRentalContractRepository>& rentalContractRepository) {
    _rentPaymentRepository = rentPaymentRepository;
    _rentalContractRepository = rentalContractRepository;
    UseCaseName = "RecordRentPayment";
}

any RecordRentPaymentUseCase::execute(const any& params) {
    auto args = any_cast<RecordRentPaymentParams>(params);

    // Validate contract exists
    auto contract = _rentalContractRepository->findById(args.contractId);
    if (contract == nullptr) {
        throw DomainException("Rental contract with ID " + to_string(args.contractId) + " does not exist");
    }

    // Validate month (1-12)
    if (args.month < 1 || args.month > 12) {
        throw DomainException("Invalid month. Must be between 1 and 12");
    }

    // Validate year
    if (args.year < 2000 || args.year > 2100) {
        throw DomainException("Invalid year. Must be between 2000 and 2100");
    }

    // Validate amount
    if (args.amountPaid < 0) {
        throw DomainException("Payment amount cannot be negative");
    }

    double expectedAmount = contract->getMonthlyRent();
    int tenantId = contract->getTenantId();

    // Check if payment record already exists for this contract and month
    if (_rentPaymentRepository->existsForContractAndMonth(args.contractId, args.month, args.year)) {
        throw DomainException("A payment record already exists for this contract in " +
            to_string(args.month) + "/" + to_string(args.year) + ". Use 'Add Partial Payment' to update.");
    }

    // Create new rent payment
    int paymentId = _rentPaymentRepository->getNextId();
    RentPayment payment(paymentId, args.contractId, tenantId, args.month, args.year,
        args.amountPaid, expectedAmount, args.paymentDate);

    if (!_rentPaymentRepository->save(payment)) {
        throw DomainException("Failed to record rent payment");
    }

    // Prepare result
    RecordRentPaymentResult result;
    result.paymentId = paymentId;
    result.contractId = args.contractId;
    result.tenantId = tenantId;
    result.month = args.month;
    result.year = args.year;
    result.amountPaid = payment.getAmountPaid();
    result.expectedAmount = expectedAmount;
    result.remainingAmount = payment.getRemainingAmount();
    result.status = payment.getStatus();

    return result;
}
