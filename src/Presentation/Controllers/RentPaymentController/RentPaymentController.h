#ifndef RENTPAYMENTCONTROLLER_H
#define RENTPAYMENTCONTROLLER_H

#include <memory>
#include <iostream>
#include "Application/UseCases/RentPayment/RecordRentPayment/RecordRentPaymentUseCase.h"
#include "Application/UseCases/RentPayment/AddPartialPayment/AddPartialPaymentUseCase.h"
#include "Application/UseCases/RentPayment/ViewPaidTenants/ViewPaidTenantsUseCase.h"
#include "Application/UseCases/RentPayment/ViewUnpaidOrPartialTenants/ViewUnpaidOrPartialTenantsUseCase.h"
#include "Application/UseCases/RentPayment/Interfaces/IRentPaymentRepository.h"

using namespace std;

class RentPaymentController {
private:
    shared_ptr<RecordRentPaymentUseCase> recordRentPaymentUseCase;
    shared_ptr<AddPartialPaymentUseCase> addPartialPaymentUseCase;
    shared_ptr<ViewPaidTenantsUseCase> viewPaidTenantsUseCase;
    shared_ptr<ViewUnpaidOrPartialTenantsUseCase> viewUnpaidOrPartialTenantsUseCase;
    shared_ptr<IRentPaymentRepository> rentPaymentRepository;

    void displayPaymentDetails(const RecordRentPaymentResult& result);
    void displayPartialPaymentResult(const AddPartialPaymentResult& result);
    void displayPaidTenantsList(const vector<PaidTenantInfo>& tenants, int month, int year);
    void displayUnpaidOrPartialTenantsList(const vector<UnpaidOrPartialTenantInfo>& tenants, int month, int year);
    string getStatusString(PaymentStatus status);
    string getMonthName(int month);

public:
    RentPaymentController(
        shared_ptr<RecordRentPaymentUseCase> recordUseCase,
        shared_ptr<AddPartialPaymentUseCase> addPartialUseCase,
        shared_ptr<ViewPaidTenantsUseCase> viewPaidUseCase,
        shared_ptr<ViewUnpaidOrPartialTenantsUseCase> viewUnpaidUseCase,
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
