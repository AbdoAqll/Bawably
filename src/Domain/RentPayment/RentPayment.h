#ifndef RENTPAYMENT_H
#define RENTPAYMENT_H

#include "PaymentStatus.h"
#include <string>

using namespace std;

class RentPayment {
private:
    int paymentId;
    int contractId;
    int tenantId;
    int month;
    int year;
    double amountPaid;
    double expectedAmount;
    PaymentStatus status;
    string paymentDate;

    void calculateStatus();

public:
    RentPayment(int id, int contractId, int tenantId, int month, int year, double expectedAmount);
    RentPayment(int id, int contractId, int tenantId, int month, int year, double amountPaid, double expectedAmount, const string& paymentDate);

    int getPaymentId() const;
    int getContractId() const;
    int getTenantId() const;
    int getMonth() const;
    int getYear() const;
    double getAmountPaid() const;
    double getExpectedAmount() const;
    PaymentStatus getStatus() const;
    string getPaymentDate() const;

    void addPayment(double amount, const string& date);
    void setAmountPaid(double amount);
    void setStatus(PaymentStatus newStatus);
    void setPaymentDate(const string& date);

    void markAsPaid(const string& date);
    void markAsPartial(double amount, const string& date);
    void markAsUnPaid();

    bool isPaid() const;
    bool isPartial() const;
    bool isUnpaid() const;
    double getRemainingAmount() const;
};

#endif // RENTPAYMENT_H