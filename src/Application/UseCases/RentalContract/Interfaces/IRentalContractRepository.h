#ifndef IRENTALCONTRACTREPOSITORY_H
#define IRENTALCONTRACTREPOSITORY_H
#include <vector>
#include <RentalContract/RentalContract.h>
using namespace std;

class IRentalContractRepository {
public:
    virtual ~IRentalContractRepository() = default;

    virtual bool save(const RentalContract& contract) = 0;
    virtual RentalContract* findById(int contractId) = 0;
    virtual RentalContract* findActiveByApartment(int apartmentId) = 0;
    virtual RentalContract* findActiveByTenant(int tenantId) = 0;
    virtual vector<RentalContract> getAll() = 0;
    virtual vector<RentalContract> getActiveContracts() = 0;

    virtual bool existsActiveContract(int apartmentId, int tenantId) = 0;
    virtual bool exists(int contractId) = 0;
    virtual bool update(const RentalContract& contract) = 0;

};
#endif //IRENTALCONTRACTREPOSITORY_H
