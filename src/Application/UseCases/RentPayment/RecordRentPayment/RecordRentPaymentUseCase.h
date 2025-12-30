#ifndef RECORDRENTPAYMENTUSECASE_H
#define RECORDRENTPAYMENTUSECASE_H

#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/RentPayment/Interfaces/IRentPaymentRepository.h>
#include <UseCases/RentalContract/Interfaces/IRentalContractRepository.h>

using namespace std;

struct RecordRentPaymentParams {
    int contractId;
    int month;
    int year;
    double amountPaid;
    string paymentDate;
};

struct RecordRentPaymentResult {
    int paymentId;
    int contractId;
    int tenantId;
    int month;
    int year;
    double amountPaid;
    double expectedAmount;
    double remainingAmount;
    PaymentStatus status;
};

class RecordRentPaymentUseCase : public IUseCase {
private:
    shared_ptr<IRentPaymentRepository> _rentPaymentRepository;
    shared_ptr<IRentalContractRepository> _rentalContractRepository;

public:
    explicit RecordRentPaymentUseCase(
        const shared_ptr<IRentPaymentRepository>& rentPaymentRepository,
        const shared_ptr<IRentalContractRepository>& rentalContractRepository);

    any execute(const any& params = {}) override;
    ~RecordRentPaymentUseCase() override = default;
};

#endif // RECORDRENTPAYMENTUSECASE_H
