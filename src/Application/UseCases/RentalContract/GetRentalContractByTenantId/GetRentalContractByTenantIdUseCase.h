#ifndef GETRENTALCONTRACTBYTENANTID_H
#define GETRENTALCONTRACTBYTENANTID_H

#include <memory>
#include <UseCases/IUseCase.h>
#include <UseCases/RentalContract/Interfaces/IRentalContractRepository.h>
#include <UseCases/User/Interfaces/IUserRepository.h>

using namespace std;

class GetRentalContractByTenantIdUseCase : public IUseCase {
private:
    shared_ptr<IRentalContractRepository> _rentalContractRepository;
    shared_ptr<IUserRepository> _userRepository;

public:
    explicit GetRentalContractByTenantIdUseCase(
        const shared_ptr<IRentalContractRepository>& rentalContractRepository,
        const shared_ptr<IUserRepository>& userRepository);

    any execute(const any& params = {}) override;
    ~GetRentalContractByTenantIdUseCase() override = default;
};

#endif //GETRENTALCONTRACTBYTENANTID_H
