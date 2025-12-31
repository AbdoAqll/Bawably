#include "TenantMenuController.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include <iostream>

using namespace std;

TenantMenuController::TenantMenuController(shared_ptr<MaintenanceRequestController> maintenanceCtrl)
    : maintenanceRequestController(maintenanceCtrl) {
}

void TenantMenuController::execute(shared_ptr<TenantUser> tenant, shared_ptr<RentalContract> contract) {
    bool running = true;

    while (running) {
        ConsoleUtils::clearScreen();
        const string tenantLabel = "Tenant Menu - " + tenant->getUsername();
        vector<string> menuOptions = {
            "1. View Maintenance History",
            "2. Create Maintenance Request",
            "0. Logout"
            };
        MenuDisplayer menu(tenantLabel, menuOptions);

        int choice = menu.show();

        switch (choice) {
        case 0:
            maintenanceRequestController->getApartmentMaintenanceHistory(
                contract->getBuildingId(),
                contract->getApartmentId()
            );
            break;
        case 1:
            maintenanceRequestController->createMaintenanceRequestForTenant(
                contract->getBuildingId(),
                contract->getApartmentId(),
                contract->getTenantId()
            );
            break;
        case 2:
        case -1:
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Logged out successfully!" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
            running = false;
            break;
        }
    }
}
