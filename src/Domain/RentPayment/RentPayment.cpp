#include "RentPayment.h"

RentPayment::RentPayment(int id, int contractId, int month, int year, double amountPaid, string &paymentDate)
{
}

int RentPayment::getPaymentId() const
{
    return 0;
}

int RentPayment::getContractId() const
{
    return 0;
}

int RentPayment::getMonth() const
{
    return 0;
}

int RentPayment::getYear() const
{
    return 0;
}

double RentPayment::getAmountPaid() const
{
    return 0.0;
}

PaymentStatus RentPayment::getStatus() const
{
    return PaymentStatus();
}

string RentPayment::getPaymentDate() const
{
    return string();
}

void RentPayment::setAmountPaid(double amount)
{
}

void RentPayment::setStatus(PaymentStatus newStatus)
{
}

void RentPayment::setPaymentDate(string &date)
{
}

void RentPayment::markAsPaid(string &date)
{
}

void RentPayment::markAsPartial(double amount, string &date)
{
}

void RentPayment::markAsUnPaid()
{
}
