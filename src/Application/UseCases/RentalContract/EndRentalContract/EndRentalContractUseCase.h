#ifndef ENDRENTALCONTRACTUSECASE_H
#define ENDRENTALCONTRACTUSECASE_H

#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/RentalContract/Interfaces/IRentalContractRepository.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
using namespace std;

struct EndRentalContractParams {
    int contractId;
    string endDate;
};

class EndRentalContractUseCase : public IUseCase {
private:
    shared_ptr<IRentalContractRepository> _rentalContractRepository;
    shared_ptr<IApartmentRepository> _apartmentRepository;

public:
    explicit EndRentalContractUseCase(
        const shared_ptr<IRentalContractRepository>& rentalContractRepository,
        const shared_ptr<IApartmentRepository>& apartmentRepository);
    
    any execute(const any& params = {}) override;
    ~EndRentalContractUseCase() override = default;
};

#endif //ENDRENTALCONTRACTUSECASE_H
