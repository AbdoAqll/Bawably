#ifndef RENTALCONTRACTCONTROLLER_H
#define RENTALCONTRACTCONTROLLER_H

#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/RentalContract/Interfaces/IRentalContractRepository.h"
#include "Application/UseCases/RentalContract/CreateRentalContract/CreateRentalContractUseCase.h"
#include "Application/UseCases/RentalContract/EndRentalContract/EndRentalContractUseCase.h"
#include "Application/UseCases/RentalContract/GetRentalContractByTenantId/GetRentalContractByTenantIdUseCase.h"
using namespace std;

class RentalContractController {
private:
    unordered_map<string, shared_ptr<IUseCase>> useCases;
    shared_ptr<IRentalContractRepository> rentalContractRepository;

    void displayContract(const RentalContract& contract);
    void displayContractList(const vector<RentalContract>& contracts);

public:
    RentalContractController(
        vector<shared_ptr<IUseCase>>& useCases,
        shared_ptr<IRentalContractRepository> repository);

    void showMenu();
    void handleCreateRentalContract(int buildingId, int apartmentId);
    void handleEndRentalContract();
    void handleViewActiveContracts();
    void handleViewAllContracts();
    void handleViewContractDetails();
    shared_ptr<RentalContract> getContractForTenantId(int tenantId);
    void execute(int buildingId, int apartmentId);
    ~RentalContractController() = default;
};

#endif //RENTALCONTRACTCONTROLLER_H
