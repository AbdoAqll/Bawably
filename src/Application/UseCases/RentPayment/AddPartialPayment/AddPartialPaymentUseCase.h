#ifndef ADDPARTIALPAYMENTUSECASE_H
#define ADDPARTIALPAYMENTUSECASE_H

#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/RentPayment/Interfaces/IRentPaymentRepository.h>
#include <UseCases/RentalContract/Interfaces/IRentalContractRepository.h>

using namespace std;

struct AddPartialPaymentParams {
    int contractId;
    int month;
    int year;
    double amount;
    string paymentDate;
};

struct AddPartialPaymentResult {
    int paymentId;
    int contractId;
    int tenantId;
    int month;
    int year;
    double previousAmount;
    double addedAmount;
    double totalAmountPaid;
    double expectedAmount;
    double remainingAmount;
    PaymentStatus previousStatus;
    PaymentStatus newStatus;
};

class AddPartialPaymentUseCase : public IUseCase {
private:
    shared_ptr<IRentPaymentRepository> _rentPaymentRepository;
    shared_ptr<IRentalContractRepository> _rentalContractRepository;

public:
    explicit AddPartialPaymentUseCase(
        const shared_ptr<IRentPaymentRepository>& rentPaymentRepository,
        const shared_ptr<IRentalContractRepository>& rentalContractRepository);

    any execute(const any& params = {}) override;
    ~AddPartialPaymentUseCase() override = default;
};

#endif // ADDPARTIALPAYMENTUSECASE_H
