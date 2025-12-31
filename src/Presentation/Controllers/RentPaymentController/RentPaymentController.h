#ifndef RENTPAYMENTCONTROLLER_H
#define RENTPAYMENTCONTROLLER_H

#include <memory>
#include <iostream>
#include <string>
#include <unordered_map>
#include <vector>
#include "Application/UseCases/IUseCase.h"
#include "Application/UseCases/RentPayment/Interfaces/IRentPaymentRepository.h"
#include "Application/UseCases/RentPayment/RecordRentPayment/RecordRentPaymentUseCase.h"
#include "Application/UseCases/RentPayment/AddPartialPayment/AddPartialPaymentUseCase.h"
#include "Application/UseCases/RentPayment/ViewPaidTenants/ViewPaidTenantsUseCase.h"
#include "Application/UseCases/RentPayment/ViewUnpaidOrPartialTenants/ViewUnpaidOrPartialTenantsUseCase.h"

using namespace std;

class RentPaymentController {
private:
    unordered_map<string, shared_ptr<IUseCase>> useCases;
    shared_ptr<IRentPaymentRepository> rentPaymentRepository;

    void displayPaymentDetails(const RecordRentPaymentResult& result);
    void displayPartialPaymentResult(const AddPartialPaymentResult& result);
    void displayPaidTenantsList(const vector<PaidTenantInfo>& tenants, int month, int year);
    void displayUnpaidOrPartialTenantsList(const vector<UnpaidOrPartialTenantInfo>& tenants, int month, int year);
    string getStatusString(PaymentStatus status);
    string getMonthName(int month);

public:
    RentPaymentController(
        vector<shared_ptr<IUseCase>>& useCases,
        shared_ptr<IRentPaymentRepository> repository);

    void execute();
    void handleRecordRentPayment();
    void handleAddPartialPayment();
    void handleViewPaidTenants();
    void handleViewUnpaidOrPartialTenants();
    void handleViewAllPayments();

    ~RentPaymentController() = default;
};

#endif // RENTPAYMENTCONTROLLER_H
