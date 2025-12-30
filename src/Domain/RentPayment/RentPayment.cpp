#include "RentPayment.h"

RentPayment::RentPayment(int id, int contractId, int tenantId, int month, int year, double expectedAmount)
    : paymentId(id), contractId(contractId), tenantId(tenantId), month(month), year(year),
    amountPaid(0.0), expectedAmount(expectedAmount), status(PaymentStatus::Unpaid), paymentDate("") {
}

RentPayment::RentPayment(int id, int contractId, int tenantId, int month, int year, double amountPaid, double expectedAmount, const string& paymentDate)
    : paymentId(id), contractId(contractId), tenantId(tenantId), month(month), year(year),
    amountPaid(amountPaid), expectedAmount(expectedAmount), paymentDate(paymentDate) {
    calculateStatus();
}

void RentPayment::calculateStatus() {
    if (amountPaid <= 0) {
        status = PaymentStatus::Unpaid;
    }
    else if (amountPaid >= expectedAmount) {
        status = PaymentStatus::Paid;
    }
    else {
        status = PaymentStatus::Partial;
    }
}

int RentPayment::getPaymentId() const {
    return paymentId;
}

int RentPayment::getContractId() const {
    return contractId;
}

int RentPayment::getTenantId() const {
    return tenantId;
}

int RentPayment::getMonth() const {
    return month;
}

int RentPayment::getYear() const {
    return year;
}

double RentPayment::getAmountPaid() const {
    return amountPaid;
}

double RentPayment::getExpectedAmount() const {
    return expectedAmount;
}

PaymentStatus RentPayment::getStatus() const {
    return status;
}

string RentPayment::getPaymentDate() const {
    return paymentDate;
}

void RentPayment::addPayment(double amount, const string& date) {
    amountPaid += amount;
    paymentDate = date;
    calculateStatus();
}

void RentPayment::setAmountPaid(double amount) {
    amountPaid = amount;
    calculateStatus();
}

void RentPayment::setStatus(PaymentStatus newStatus) {
    status = newStatus;
}

void RentPayment::setPaymentDate(const string& date) {
    paymentDate = date;
}

void RentPayment::markAsPaid(const string& date) {
    amountPaid = expectedAmount;
    paymentDate = date;
    status = PaymentStatus::Paid;
}

void RentPayment::markAsPartial(double amount, const string& date) {
    amountPaid = amount;
    paymentDate = date;
    calculateStatus();
}

void RentPayment::markAsUnPaid() {
    amountPaid = 0.0;
    paymentDate = "";
    status = PaymentStatus::Unpaid;
}

bool RentPayment::isPaid() const {
    return status == PaymentStatus::Paid;
}

bool RentPayment::isPartial() const {
    return status == PaymentStatus::Partial;
}

bool RentPayment::isUnpaid() const {
    return status == PaymentStatus::Unpaid;
}

double RentPayment::getRemainingAmount() const {
    return expectedAmount - amountPaid;
}