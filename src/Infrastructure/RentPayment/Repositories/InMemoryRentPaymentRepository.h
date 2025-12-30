#ifndef INMEMORYRENTPAYMENTREPOSITORY_H
#define INMEMORYRENTPAYMENTREPOSITORY_H

#include "Application/UseCases/RentPayment/Interfaces/IRentPaymentRepository.h"
#include <map>
#include <vector>

using namespace std;

class InMemoryRentPaymentRepository : public IRentPaymentRepository {
private:
    map<int, RentPayment> payments;
    int nextId;

public:
    InMemoryRentPaymentRepository();
    ~InMemoryRentPaymentRepository() override = default;

    bool save(const RentPayment& payment) override;
    bool update(const RentPayment& payment) override;
    RentPayment* findById(int paymentId) override;
    RentPayment* findByContractAndMonth(int contractId, int month, int year) override;
    vector<RentPayment> findByContract(int contractId) override;
    vector<RentPayment> findByTenant(int tenantId) override;
    vector<RentPayment> findByMonth(int month, int year) override;
    vector<RentPayment> findByStatus(PaymentStatus status, int month, int year) override;
    vector<RentPayment> getAll() override;
    bool exists(int paymentId) override;
    bool existsForContractAndMonth(int contractId, int month, int year) override;
    int getNextId() override;
};

#endif // INMEMORYRENTPAYMENTREPOSITORY_H
