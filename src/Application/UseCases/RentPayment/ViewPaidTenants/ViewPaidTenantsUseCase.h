#ifndef VIEWPAIDTENANTSUSECASE_H
#define VIEWPAIDTENANTSUSECASE_H

#include <memory>
#include <vector>
#include <UseCases/IUseCase.h>
#include <UseCases/RentPayment/Interfaces/IRentPaymentRepository.h>
#include <UseCases/RentalContract/Interfaces/IRentalContractRepository.h>
#include <UseCases/User/Interfaces/IUserRepository.h>

using namespace std;

struct ViewPaidTenantsParams {
    int month;
    int year;
};

struct PaidTenantInfo {
    int tenantId;
    string tenantName;
    int contractId;
    int apartmentId;
    int buildingId;
    double amountPaid;
    double expectedAmount;
    string paymentDate;
};

class ViewPaidTenantsUseCase : public IUseCase {
private:
    shared_ptr<IRentPaymentRepository> _rentPaymentRepository;
    shared_ptr<IRentalContractRepository> _rentalContractRepository;
    shared_ptr<IUserRepository> _userRepository;

public:
    explicit ViewPaidTenantsUseCase(
        const shared_ptr<IRentPaymentRepository>& rentPaymentRepository,
        const shared_ptr<IRentalContractRepository>& rentalContractRepository,
        const shared_ptr<IUserRepository>& userRepository);

    any execute(const any& params = {}) override;
    ~ViewPaidTenantsUseCase() override = default;
};

#endif // VIEWPAIDTENANTSUSECASE_H
