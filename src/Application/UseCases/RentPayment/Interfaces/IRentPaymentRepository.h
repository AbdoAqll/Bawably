#ifndef IRENTPAYMENTREPOSITORY_H
#define IRENTPAYMENTREPOSITORY_H

#include <vector>
#include <RentPayment/RentPayment.h>
#include <RentPayment/PaymentStatus.h>

using namespace std;

class IRentPaymentRepository {
public:
    virtual ~IRentPaymentRepository() = default;

    virtual bool save(const RentPayment& payment) = 0;
    virtual bool update(const RentPayment& payment) = 0;
    virtual RentPayment* findById(int paymentId) = 0;
    virtual RentPayment* findByContractAndMonth(int contractId, int month, int year) = 0;
    virtual vector<RentPayment> findByContract(int contractId) = 0;
    virtual vector<RentPayment> findByTenant(int tenantId) = 0;
    virtual vector<RentPayment> findByMonth(int month, int year) = 0;
    virtual vector<RentPayment> findByStatus(PaymentStatus status, int month, int year) = 0;
    virtual vector<RentPayment> getAll() = 0;
    virtual bool exists(int paymentId) = 0;
    virtual bool existsForContractAndMonth(int contractId, int month, int year) = 0;
    virtual int getNextId() = 0;
};

#endif // IRENTPAYMENTREPOSITORY_H
