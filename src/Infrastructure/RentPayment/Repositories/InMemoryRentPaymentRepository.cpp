#include "InMemoryRentPaymentRepository.h"

InMemoryRentPaymentRepository::InMemoryRentPaymentRepository() {
    nextId = 1;

    // contract 1 payment all over the year
    RentPayment payment1(nextId++, 1, 2, 12, 2025, 5000.0, 5000.0, "2025-12-01");
    payments.insert({ payment1.getPaymentId(), payment1 });

    RentPayment payment2(nextId++, 1, 2, 11, 2025, 5000.0, 5000.0, "2025-11-01");
    payments.insert({ payment2.getPaymentId(), payment2 });

    RentPayment payment3(nextId++, 1, 2, 10, 2025, 5000.0, 5000.0, "2025-10-01");
    payments.insert({ payment3.getPaymentId(), payment3 });

    RentPayment payment4(nextId++, 1, 2, 9, 2025, 5000.0, 5000.0, "2025-09-01");
    payments.insert({ payment4.getPaymentId(), payment4 });

    RentPayment payment5(nextId++, 1, 2, 8, 2025, 5000.0, 5000.0, "2025-08-01");
    payments.insert({ payment5.getPaymentId(), payment5 });

    RentPayment payment6(nextId++, 1, 2, 7, 2025, 5000.0, 5000.0, "2025-07-01");
    payments.insert({ payment6.getPaymentId(), payment6 });

    RentPayment payment7(nextId++, 1, 2, 6, 2025, 5000.0, 5000.0, "2025-06-01");
    payments.insert({ payment7.getPaymentId(), payment7 });

    RentPayment payment8(nextId++, 1, 2, 5, 2025, 5000.0, 5000.0, "2025-05-01");
    payments.insert({ payment8.getPaymentId(), payment8 });

    RentPayment payment9(nextId++, 1, 2, 4, 2025, 5000.0, 5000.0, "2025-04-01");
    payments.insert({ payment9.getPaymentId(), payment9 });

    RentPayment payment10(nextId++, 1, 2, 3, 2025, 5000.0, 5000.0, "2025-03-01");
    payments.insert({ payment10.getPaymentId(), payment10 });

    RentPayment payment11(nextId++, 1, 2, 2, 2025, 5000.0, 5000.0, "2025-02-01");
    payments.insert({ payment11.getPaymentId(), payment11 });

    RentPayment payment12(nextId++, 1, 2, 1, 2025, 4000.0, 5000.0, "2025-01-01");
    payments.insert({ payment12.getPaymentId(), payment12 });




    // contract 2 payment all over the years
    RentPayment payment13(nextId++, 2, 3, 12, 2025, 6000.0, 6000.0, "2025-12-01");
    payments.insert({ payment13.getPaymentId(), payment13 });

    RentPayment payment14(nextId++, 2, 3, 11, 2025, 6000.0, 6000.0, "2025-11-01");
    payments.insert({ payment14.getPaymentId(), payment14 });

    RentPayment payment15(nextId++, 2, 3, 10, 2025, 6000.0, 6000.0, "2025-10-01");
    payments.insert({ payment15.getPaymentId(), payment15 });

    RentPayment payment16(nextId++, 2, 3, 9, 2025, 6000.0, 6000.0, "2025-09-01");
    payments.insert({ payment16.getPaymentId(), payment16 });

    RentPayment payment17(nextId++, 2, 3, 8, 2025, 6000.0, 6000.0, "2025-08-01");
    payments.insert({ payment17.getPaymentId(), payment17 });

    RentPayment payment18(nextId++, 2, 3, 7, 2025, 6000.0, 6000.0, "2025-07-01");
    payments.insert({ payment18.getPaymentId(), payment18 });

    RentPayment payment19(nextId++, 2, 3, 6, 2025, 6000.0, 6000.0, "2025-06-01");
    payments.insert({ payment19.getPaymentId(), payment19 });

    RentPayment payment20(nextId++, 2, 3, 5, 2025, 6000.0, 6000.0, "2025-05-01");
    payments.insert({ payment20.getPaymentId(), payment20 });

    RentPayment payment21(nextId++, 2, 3, 4, 2025, 6000.0, 6000.0, "2025-04-01");
    payments.insert({ payment21.getPaymentId(), payment21 });

    RentPayment payment22(nextId++, 2, 3, 3, 2025, 6000.0, 6000.0, "2025-03-01");
    payments.insert({ payment22.getPaymentId(), payment22 });

    RentPayment payment23(nextId++, 2, 3, 2, 2025, 6000.0, 6000.0, "2025-02-01");
    payments.insert({ payment23.getPaymentId(), payment23 });

    RentPayment payment24(nextId++, 2, 3, 1, 2025, 5000.0, 6000.0, "2025-01-01");
    payments.insert({ payment24.getPaymentId(), payment24 });



    // contract 3 payment all over the year
    RentPayment payment25(nextId++, 3, 4, 12, 2025, 7000.0, 7000.0, "2025-12-01");
    payments.insert({ payment25.getPaymentId(), payment25 });

    RentPayment payment26(nextId++, 3, 4, 11, 2025, 7000.0, 7000.0, "2025-11-01");
    payments.insert({ payment26.getPaymentId(), payment26 });

    RentPayment payment27(nextId++, 3, 4, 10, 2025, 7000.0, 7000.0, "2025-10-01");
    payments.insert({ payment27.getPaymentId(), payment27 });

    RentPayment payment28(nextId++, 3, 4, 9, 2025, 7000.0, 7000.0, "2025-09-01");
    payments.insert({ payment28.getPaymentId(), payment28 });

    RentPayment payment29(nextId++, 3, 4, 8, 2025, 7000.0, 7000.0, "2025-08-01");
    payments.insert({ payment29.getPaymentId(), payment29 });

    RentPayment payment30(nextId++, 3, 4, 7, 2025, 7000.0, 7000.0, "2025-07-01");
    payments.insert({ payment30.getPaymentId(), payment30 });

    RentPayment payment31(nextId++, 3, 4, 6, 2025, 7000.0, 7000.0, "2025-06-01");
    payments.insert({ payment31.getPaymentId(), payment31 });

    RentPayment payment32(nextId++, 3, 4, 5, 2025, 7000.0, 7000.0, "2025-05-01");
    payments.insert({ payment32.getPaymentId(), payment32 });

    RentPayment payment33(nextId++, 3, 4, 4, 2025, 7000.0, 7000.0, "2025-04-01");
    payments.insert({ payment33.getPaymentId(), payment33 });

    RentPayment payment34(nextId++, 3, 4, 3, 2025, 7000.0, 7000.0, "2025-03-01");
    payments.insert({ payment34.getPaymentId(), payment34 });

    RentPayment payment35(nextId++, 3, 4, 2, 2025, 7000.0, 7000.0, "2025-02-01");
    payments.insert({ payment35.getPaymentId(), payment35 });

    RentPayment payment36(nextId++, 3, 4, 1, 2025, 6000.0, 7000.0, "2025-01-01");
    payments.insert({ payment36.getPaymentId(), payment36 });
}

bool InMemoryRentPaymentRepository::save(const RentPayment& payment) {
    int id = payment.getPaymentId();

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
