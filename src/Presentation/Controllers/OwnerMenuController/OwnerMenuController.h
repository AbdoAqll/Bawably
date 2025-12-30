#ifndef OWNERMENUCONTROLLER_H
#define OWNERMENUCONTROLLER_H

#include <memory>
#include "Domain/User/Owner.h"
#include "Controllers/BuildingController/BuildingController.h"
#include "Controllers/RentPaymentController/RentPaymentController.h"

using namespace std;

class OwnerMenuController {
private:
    shared_ptr<BuildingController> buildingController;
    shared_ptr<RentPaymentController> rentPaymentController;

public:
    explicit OwnerMenuController(
        shared_ptr<BuildingController> buildingCtrl,
        shared_ptr<RentPaymentController> rentPaymentCtrl);

    void execute(shared_ptr<Owner> owner);

    ~OwnerMenuController() = default;
};

#endif // OWNERMENUCONTROLLER_H
