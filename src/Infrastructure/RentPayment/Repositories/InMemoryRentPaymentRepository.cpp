#include "InMemoryRentPaymentRepository.h"

InMemoryRentPaymentRepository::InMemoryRentPaymentRepository() {
    nextId = 1;

    RentPayment payment1(nextId++, 1, 1, 12, 2025, 2000.0, 2000.0, "2025-12-01");
    payments.insert({ payment1.getPaymentId(), payment1 });

    RentPayment payment2(nextId++, 2, 2, 12, 2025, 2200.0, 2200.0, "2025-12-05");
    payments.insert({ payment2.getPaymentId(), payment2 });
    
    RentPayment payment3(nextId++, 3, 3, 12, 2025, 1000.0, 1800.0, "2025-12-10");
    payments.insert({ payment3.getPaymentId(), payment3 });

    RentPayment payment4(nextId++, 1, 1, 11, 2025, 2000.0, 2000.0, "2025-11-01");
    payments.insert({ payment4.getPaymentId(), payment4 });

    RentPayment payment5(nextId++, 2, 2, 11, 2025, 2200.0, 2200.0, "2025-11-02");
    payments.insert({ payment5.getPaymentId(), payment5 });

    RentPayment payment6(nextId++, 3, 3, 11, 2025, 1800.0, 1800.0, "2025-11-03");
    payments.insert({ payment6.getPaymentId(), payment6 });
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
