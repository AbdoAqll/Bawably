#include "InMemoryRentalContractRepository.h"

InMemoryRentalContractRepository::InMemoryRentalContractRepository() {
    nextId = 1;
    string rc1date = "2025-01-01";
    RentalContract rc1 (nextId++, 1, 2, 5000, rc1date);
    contracts.insert({rc1.getContractId(), rc1});

    string rc2date = "2025-01-01";
    RentalContract rc2 (nextId++, 4, 3, 6000, rc2date);
    contracts.insert({rc2.getContractId(), rc2});

    string rc3date = "2025-01-01";
    RentalContract rc3 (nextId++, 7, 4, 7000, rc3date);
    contracts.insert({rc3.getContractId(), rc3});
}

bool InMemoryRentalContractRepository::save(const RentalContract& contract) {
    int id = contract.getContractId();

    if (contracts.find(id) != contracts.end()) {
        return false;
    }

    contracts.insert({ id, contract });
    return true;
}

RentalContract* InMemoryRentalContractRepository::findById(int contractId) {
    auto it = contracts.find(contractId);
    if (it != contracts.end()) {
        return &(it->second);
    }
    return nullptr;
}

RentalContract* InMemoryRentalContractRepository::findActiveByApartment(int apartmentId) {
    for (auto& pair : contracts) {
        if (pair.second.getApartmentId() == apartmentId && pair.second.getIsActive()) {
            return &(pair.second);
        }
    }
    return nullptr;
}

RentalContract* InMemoryRentalContractRepository::findActiveByTenant(int tenantId) {
    for (auto& pair : contracts) {
        if (pair.second.getTenantId() == tenantId && pair.second.getIsActive()) {
            return &(pair.second);
        }
    }
    return nullptr;
}

vector<RentalContract> InMemoryRentalContractRepository::getAll() {
    vector<RentalContract> allContracts;
    for (const auto& pair : contracts) {
        allContracts.push_back(pair.second);
    }
    return allContracts;
}

vector<RentalContract> InMemoryRentalContractRepository::getActiveContracts() {
    vector<RentalContract> activeContracts;
    for (const auto& pair : contracts) {
        if (pair.second.getIsActive()) {
            activeContracts.push_back(pair.second);
        }
    }
    return activeContracts;
}

bool InMemoryRentalContractRepository::existsActiveContract(int apartmentId, int tenantId) {
    for (const auto& pair : contracts) {
        if (pair.second.getIsActive()) {
            if (pair.second.getApartmentId() == apartmentId ||
                pair.second.getTenantId() == tenantId) {
                return true;
            }
        }
    }
    return false;
}

bool InMemoryRentalContractRepository::exists(int contractId) {
    return contracts.find(contractId) != contracts.end();
}

bool InMemoryRentalContractRepository::update(const RentalContract& contract) {
    int id = contract.getContractId();

    if (contracts.find(id) == contracts.end()) {
        return false;
    }

    contracts.at(id) = contract;
    return true;
}
