#ifndef RENTALCONTRACTCONTROLLER_H
#define RENTALCONTRACTCONTROLLER_H

#include <memory>
#include <iostream>
#include <UseCases/RentalContract/GetRentalContractByTenantId/GetRentalContractByTenantIdUseCase.h>

#include "Application/UseCases/RentalContract/CreateRentalContract/CreateRentalContractUseCase.h"
#include "Application/UseCases/RentalContract/EndRentalContract/EndRentalContractUseCase.h"
#include "Application/UseCases/RentalContract/Interfaces/IRentalContractRepository.h"
using namespace std;

class RentalContractController {
private:
    shared_ptr<CreateRentalContractUseCase> createRentalContractUseCase;
    shared_ptr<EndRentalContractUseCase> endRentalContractUseCase;
    shared_ptr<GetRentalContractByTenantIdUseCase> getRentalContractByTenantId;
    shared_ptr<IRentalContractRepository> rentalContractRepository;

    void displayContract(const RentalContract& contract);
    void displayContractList(const vector<RentalContract>& contracts);

public:
    RentalContractController(
        shared_ptr<CreateRentalContractUseCase> createUseCase,
        shared_ptr<EndRentalContractUseCase> endUseCase,
        shared_ptr<GetRentalContractByTenantIdUseCase> getRentalContractByTenId,
        shared_ptr<IRentalContractRepository> repository);

    void showMenu();
    void handleCreateRentalContract(int buildingId , int apartmentId);
    void handleEndRentalContract();
    void handleViewActiveContracts();
    void handleViewAllContracts();
    void handleViewContractDetails();
    shared_ptr<RentalContract> getContractForTenantId(int tenantId);
    void execute(int buildingId , int apartmentId);
    ~RentalContractController() = default;
};

#endif //RENTALCONTRACTCONTROLLER_H
