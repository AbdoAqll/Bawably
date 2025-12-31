#ifndef OWNERMENUCONTROLLER_H
#define OWNERMENUCONTROLLER_H

#include <memory>
#include <Controllers/TenantController/TenantController.h>

#include "Domain/User/Owner.h"
#include "Controllers/BuildingController/BuildingController.h"
#include "Controllers/RentPaymentController/RentPaymentController.h"
#include "Controllers/ExpenseController/ExpenseController.h"

using namespace std;

class OwnerMenuController {
private:
    shared_ptr<BuildingController> buildingController;
    shared_ptr<RentPaymentController> rentPaymentController;
    shared_ptr<TenantController> tenantController;
    shared_ptr<ExpenseController> expenseController;

public:
    explicit OwnerMenuController(
        shared_ptr<BuildingController> buildingCtrl,
        shared_ptr<RentPaymentController> rentPaymentCtrl,
        shared_ptr<TenantController> tenantCtrl,
        shared_ptr<ExpenseController> expenseCtrl);

    void execute(shared_ptr<Owner> owner);

    ~OwnerMenuController() = default;
};

#endif // OWNERMENUCONTROLLER_H
