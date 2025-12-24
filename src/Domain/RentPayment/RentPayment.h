#include "PaymentStatus.h"
#include<string>

using namespace std;

class RentPayment
{
private:
    int paymentId;
    int contractId;
    int month;
    int year;
    double amountPaid;
    PaymentStatus status;
    string paymentDate;
public:
    RentPayment(int id, int contractId, int month, int year, double amountPaid, string& paymentDate);

    int getPaymentId() const;
    int getContractId() const;
    int getMonth() const;
    int getYear() const;
    double getAmountPaid() const;
    PaymentStatus getStatus() const;
    string getPaymentDate() const;

    void setAmountPaid(double amount);
    void setStatus(PaymentStatus newStatus);
    void setPaymentDate(string& date);

    void markAsPaid(string& date);
    void markAsPartial(double amount, string& date);
    void markAsUnPaid();
};