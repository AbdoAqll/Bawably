#ifndef OWNERMENUCONTROLLER_H
#define OWNERMENUCONTROLLER_H

#include <memory>
#include "Domain/User/Owner.h"
#include "Controllers/BuildingController/BuildingController.h"

using namespace std;

class OwnerMenuController {
private:
    shared_ptr<BuildingController> buildingController;

public:
    explicit OwnerMenuController(shared_ptr<BuildingController> buildingCtrl);

    void execute(shared_ptr<Owner> owner);

    ~OwnerMenuController() = default;
};

#endif // OWNERMENUCONTROLLER_H
