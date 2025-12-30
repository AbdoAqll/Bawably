#ifndef VIEWUNPAIDORPARTIALTENANTSUSECASE_H
#define VIEWUNPAIDORPARTIALTENANTSUSECASE_H

#include <memory>
#include <vector>
#include <UseCases/IUseCase.h>
#include <UseCases/RentPayment/Interfaces/IRentPaymentRepository.h>
#include <UseCases/RentalContract/Interfaces/IRentalContractRepository.h>
#include <UseCases/User/Interfaces/IUserRepository.h>

using namespace std;

struct ViewUnpaidOrPartialTenantsParams {
    int month;
    int year;
};

struct UnpaidOrPartialTenantInfo {
    int tenantId;
    string tenantName;
    int contractId;
    int apartmentId;
    int buildingId;
    double amountPaid;
    double expectedAmount;
    double remainingAmount;
    PaymentStatus status;
    string paymentDate;
};

class ViewUnpaidOrPartialTenantsUseCase : public IUseCase {
private:
    shared_ptr<IRentPaymentRepository> _rentPaymentRepository;
    shared_ptr<IRentalContractRepository> _rentalContractRepository;
    shared_ptr<IUserRepository> _userRepository;

public:
    explicit ViewUnpaidOrPartialTenantsUseCase(
        const shared_ptr<IRentPaymentRepository>& rentPaymentRepository,
        const shared_ptr<IRentalContractRepository>& rentalContractRepository,
        const shared_ptr<IUserRepository>& userRepository);

    any execute(const any& params = {}) override;
    ~ViewUnpaidOrPartialTenantsUseCase() override = default;
};

#endif // VIEWUNPAIDORPARTIALTENANTSUSECASE_H
