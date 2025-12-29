#ifndef CREATERENTALCONTRACTUSECASE_H
#define CREATERENTALCONTRACTUSECASE_H

#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/RentalContract/Interfaces/IRentalContractRepository.h>
#include <UseCases/Apartment/Interfaces/IApartmentRepository.h>
#include <UseCases/User/Interfaces/IUserRepository.h>

using namespace std;

struct CreateRentalContractParams {
    int buildingId;
    int apartmentId;
    int tenantId;
    double monthlyRent;
    string startDate;
};

class CreateRentalContractUseCase : public IUseCase {
private:
    shared_ptr<IRentalContractRepository> _rentalContractRepository;
    shared_ptr<IApartmentRepository> _apartmentRepository;
    shared_ptr<IUserRepository> _userRepository;

public:
    explicit CreateRentalContractUseCase(
        const shared_ptr<IRentalContractRepository>& rentalContractRepository,
        const shared_ptr<IApartmentRepository>& apartmentRepository,
        const shared_ptr<IUserRepository>& userRepository);

    any execute(const any& params = {}) override;
    ~CreateRentalContractUseCase() override = default;
};

#endif //CREATERENTALCONTRACTUSECASE_H
