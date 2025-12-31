#include "RecordRentPaymentUseCase.h"
#include "Domain/RentalContract/Exceptions/RentalContractNotFoundException.h"
#include "Domain/Shared/InvalidMonthException.h"
#include "Domain/Shared/InvalidYearException.h"
#include "Domain/RentPayment/Exceptions/InvalidPaymentAmountException.h"
#include "Domain/RentPayment/Exceptions/PaymentRecordExistsException.h"
#include "Domain/RentPayment/Exceptions/PaymentCreationFailedException.h"

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
        throw RentalContractNotFoundException(args.contractId);
    }

    // Validate month (1-12)
    if (args.month < 1 || args.month > 12) {
        throw InvalidMonthException(args.month);
    }

    // Validate year
    if (args.year < 2000 || args.year > 2100) {
        throw InvalidYearException(args.year);
    }

    // Validate amount
    if (args.amountPaid < 0) {
        throw InvalidPaymentAmountException(args.amountPaid);
    }

    double expectedAmount = contract->getMonthlyRent();
    int tenantId = contract->getTenantId();

    // Check if payment record already exists for this contract and month
    if (_rentPaymentRepository->existsForContractAndMonth(args.contractId, args.month, args.year)) {
        throw PaymentRecordExistsException(args.contractId, args.month, args.year);
    }

    // Create new rent payment
    int paymentId = _rentPaymentRepository->getNextId();
    RentPayment payment(paymentId, args.contractId, tenantId, args.month, args.year,
        args.amountPaid, expectedAmount, args.paymentDate);

    if (!_rentPaymentRepository->save(payment)) {
        throw PaymentCreationFailedException();
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
