#ifndef INMEMORYRENTALCONTRACTREPOSITORY_H
#define INMEMORYRENTALCONTRACTREPOSITORY_H

#include "Application/UseCases/RentalContract/Interfaces/IRentalContractRepository.h"
#include <map>
#include <vector>
using namespace std;

class InMemoryRentalContractRepository : public IRentalContractRepository {
private:
    map<int, RentalContract> contracts;
    int nextId;

public:
    InMemoryRentalContractRepository();
    ~InMemoryRentalContractRepository() override = default;

    bool save(const RentalContract &contract) override;
    RentalContract* findById(int contractId) override;
    RentalContract* findActiveByApartment(int apartmentId) override;
    RentalContract* findActiveByTenant(int tenantId) override;
    vector<RentalContract> getAll() override;
    vector<RentalContract> getActiveContracts() override;
    bool existsActiveContract(int apartmentId, int tenantId) override;
    bool exists(int contractId) override;
    bool update(const RentalContract &contract) override;
};

#endif //INMEMORYRENTALCONTRACTREPOSITORY_H
