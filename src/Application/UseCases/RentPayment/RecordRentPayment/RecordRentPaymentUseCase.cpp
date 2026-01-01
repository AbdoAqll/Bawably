#include "RecordRentPaymentUseCase.h"
#include "Domain/RentalContract/Exceptions/RentalContractNotFoundException.h"
#include "Domain/Shared/InvalidMonthException.h"
#include "Domain/Shared/InvalidYearException.h"
#include "Domain/RentPayment/Exceptions/InvalidPaymentAmountException.h"
#include "Domain/RentPayment/Exceptions/PaymentExceedsExpectedException.h"
#include "Domain/RentPayment/Exceptions/PaymentCreationFailedException.h"
#include "Domain/RentPayment/Exceptions/PaymentUpdateFailedException.h"

RecordRentPaymentUseCase::RecordRentPaymentUseCase(
    const shared_ptr<IRentPaymentRepository>& rentPaymentRepository,
    const shared_ptr<IRentalContractRepository>& rentalContractRepository) {
    _rentPaymentRepository = rentPaymentRepository;
    _rentalContractRepository = rentalContractRepository;
    UseCaseName = "RecordRentPayment";
}

any RecordRentPaymentUseCase::execute(const any& params) {
    auto args = any_cast<RecordRentPaymentParams>(params);

    auto contract = _rentalContractRepository->findById(args.contractId);
    if (contract == nullptr) {
        throw RentalContractNotFoundException(args.contractId);
    }

    if (args.month < 1 || args.month > 12) {
        throw InvalidMonthException(args.month);
    }

    if (args.year < 2000 || args.year > 2100) {
        throw InvalidYearException(args.year);
    }

    if (args.amount <= 0) {
        throw InvalidPaymentAmountException(args.amount, true);
    }

    double expectedAmount = contract->getMonthlyRent();
    int tenantId = contract->getTenantId();

    auto existingPayment = _rentPaymentRepository->findByContractAndMonth(args.contractId, args.month, args.year);

    RecordRentPaymentResult result;

    if (existingPayment != nullptr) {
        result.paymentId = existingPayment->getPaymentId();
        result.previousAmount = existingPayment->getAmountPaid();
        result.previousStatus = existingPayment->getStatus();
        result.isNewRecord = false;

        double totalAfterPayment = existingPayment->getAmountPaid() + args.amount;
        if (totalAfterPayment > expectedAmount) {
            throw PaymentExceedsExpectedException(totalAfterPayment, expectedAmount, existingPayment->getRemainingAmount());
        }

        existingPayment->addPayment(args.amount, args.paymentDate);

        if (!_rentPaymentRepository->update(*existingPayment)) {
            throw PaymentUpdateFailedException(existingPayment->getPaymentId());
        }

        result.totalAmountPaid = existingPayment->getAmountPaid();
        result.newStatus = existingPayment->getStatus();
        result.remainingAmount = existingPayment->getRemainingAmount();
    }
    else {
        if (args.amount > expectedAmount) {
            throw PaymentExceedsExpectedException(args.amount, expectedAmount, expectedAmount);
        }

        int paymentId = _rentPaymentRepository->getNextId();
        RentPayment newPayment(paymentId, args.contractId, tenantId, args.month, args.year,
            args.amount, expectedAmount, args.paymentDate);

        if (!_rentPaymentRepository->save(newPayment)) {
            throw PaymentCreationFailedException();
        }

        result.paymentId = paymentId;
        result.previousAmount = 0.0;
        result.previousStatus = PaymentStatus::Unpaid;
        result.totalAmountPaid = newPayment.getAmountPaid();
        result.newStatus = newPayment.getStatus();
        result.remainingAmount = newPayment.getRemainingAmount();
        result.isNewRecord = true;
    }

    result.contractId = args.contractId;
    result.tenantId = tenantId;
    result.month = args.month;
    result.year = args.year;
    result.addedAmount = args.amount;
    result.expectedAmount = expectedAmount;

    return result;
}
