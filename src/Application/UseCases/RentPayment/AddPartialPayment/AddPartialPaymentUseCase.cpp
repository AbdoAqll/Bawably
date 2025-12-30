#include "AddPartialPaymentUseCase.h"
#include "Domain/Shared/DomainException.h"

AddPartialPaymentUseCase::AddPartialPaymentUseCase(
    const shared_ptr<IRentPaymentRepository>& rentPaymentRepository,
    const shared_ptr<IRentalContractRepository>& rentalContractRepository) {
    _rentPaymentRepository = rentPaymentRepository;
    _rentalContractRepository = rentalContractRepository;
    UseCaseName = "AddPartialPayment";
}

any AddPartialPaymentUseCase::execute(const any& params) {
    auto args = any_cast<AddPartialPaymentParams>(params);

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
    if (args.amount <= 0) {
        throw DomainException("Payment amount must be positive");
    }

    double expectedAmount = contract->getMonthlyRent();
    int tenantId = contract->getTenantId();

    // Check if payment record exists for this contract and month
    auto payment = _rentPaymentRepository->findByContractAndMonth(args.contractId, args.month, args.year);

    AddPartialPaymentResult result;

    if (payment != nullptr) {
        // Payment record exists - add to it
        result.paymentId = payment->getPaymentId();
        result.previousAmount = payment->getAmountPaid();
        result.previousStatus = payment->getStatus();

        // Add the partial payment
        payment->addPayment(args.amount, args.paymentDate);

        if (!_rentPaymentRepository->update(*payment)) {
            throw DomainException("Failed to update rent payment");
        }

        result.totalAmountPaid = payment->getAmountPaid();
        result.newStatus = payment->getStatus();
        result.remainingAmount = payment->getRemainingAmount();
    }
    else {
        // Create new payment record with partial amount
        int paymentId = _rentPaymentRepository->getNextId();
        RentPayment newPayment(paymentId, args.contractId, tenantId, args.month, args.year,
            args.amount, expectedAmount, args.paymentDate);

        if (!_rentPaymentRepository->save(newPayment)) {
            throw DomainException("Failed to create rent payment");
        }

        result.paymentId = paymentId;
        result.previousAmount = 0.0;
        result.previousStatus = PaymentStatus::Unpaid;
        result.totalAmountPaid = newPayment.getAmountPaid();
        result.newStatus = newPayment.getStatus();
        result.remainingAmount = newPayment.getRemainingAmount();
    }

    result.contractId = args.contractId;
    result.tenantId = tenantId;
    result.month = args.month;
    result.year = args.year;
    result.addedAmount = args.amount;
    result.expectedAmount = expectedAmount;

    return result;
}
