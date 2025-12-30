#include "InMemoryRentPaymentRepository.h"

InMemoryRentPaymentRepository::InMemoryRentPaymentRepository() {
    nextId = 1;
}

bool InMemoryRentPaymentRepository::save(const RentPayment& payment) {
    int id = payment.getPaymentId();

    // Check if payment already exists
    if (payments.find(id) != payments.end()) {
        return false;
    }

    payments.insert({ id, payment });
    if (id >= nextId) {
        nextId = id + 1;
    }
    return true;
}

bool InMemoryRentPaymentRepository::update(const RentPayment& payment) {
    int id = payment.getPaymentId();

    if (payments.find(id) == payments.end()) {
        return false;
    }

    payments.at(id) = payment;
    return true;
}

RentPayment* InMemoryRentPaymentRepository::findById(int paymentId) {
    auto it = payments.find(paymentId);
    if (it != payments.end()) {
        return &(it->second);
    }
    return nullptr;
}

RentPayment* InMemoryRentPaymentRepository::findByContractAndMonth(int contractId, int month, int year) {
    for (auto& pair : payments) {
        if (pair.second.getContractId() == contractId &&
            pair.second.getMonth() == month &&
            pair.second.getYear() == year) {
            return &(pair.second);
        }
    }
    return nullptr;
}

vector<RentPayment> InMemoryRentPaymentRepository::findByContract(int contractId) {
    vector<RentPayment> result;
    for (const auto& pair : payments) {
        if (pair.second.getContractId() == contractId) {
            result.push_back(pair.second);
        }
    }
    return result;
}

vector<RentPayment> InMemoryRentPaymentRepository::findByTenant(int tenantId) {
    vector<RentPayment> result;
    for (const auto& pair : payments) {
        if (pair.second.getTenantId() == tenantId) {
            result.push_back(pair.second);
        }
    }
    return result;
}

vector<RentPayment> InMemoryRentPaymentRepository::findByMonth(int month, int year) {
    vector<RentPayment> result;
    for (const auto& pair : payments) {
        if (pair.second.getMonth() == month && pair.second.getYear() == year) {
            result.push_back(pair.second);
        }
    }
    return result;
}

vector<RentPayment> InMemoryRentPaymentRepository::findByStatus(PaymentStatus status, int month, int year) {
    vector<RentPayment> result;
    for (const auto& pair : payments) {
        if (pair.second.getStatus() == status &&
            pair.second.getMonth() == month &&
            pair.second.getYear() == year) {
            result.push_back(pair.second);
        }
    }
    return result;
}

vector<RentPayment> InMemoryRentPaymentRepository::getAll() {
    vector<RentPayment> result;
    for (const auto& pair : payments) {
        result.push_back(pair.second);
    }
    return result;
}

bool InMemoryRentPaymentRepository::exists(int paymentId) {
    return payments.find(paymentId) != payments.end();
}

bool InMemoryRentPaymentRepository::existsForContractAndMonth(int contractId, int month, int year) {
    for (const auto& pair : payments) {
        if (pair.second.getContractId() == contractId &&
            pair.second.getMonth() == month &&
            pair.second.getYear() == year) {
            return true;
        }
    }
    return false;
}

int InMemoryRentPaymentRepository::getNextId() {
    return nextId++;
}
