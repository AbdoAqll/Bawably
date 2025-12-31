#include "OwnerMenuController.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include <iostream>

using namespace std;

OwnerMenuController::OwnerMenuController(
    shared_ptr<BuildingController> buildingCtrl,
    shared_ptr<RentPaymentController> rentPaymentCtrl,
    shared_ptr<TenantController> tenantCtrl,
    shared_ptr<ExpenseController> expenseCtrl,
    shared_ptr<ReportsController> reportsCtrl)
    : buildingController(buildingCtrl), rentPaymentController(rentPaymentCtrl),
    tenantController(tenantCtrl), expenseController(expenseCtrl), reportsController(reportsCtrl) {
}

void OwnerMenuController::execute(shared_ptr<Owner> owner) {
    bool running = true;

    while (running) {
        ConsoleUtils::clearScreen();
        ConsoleUtils::textattr(Colors::LABEL);

        const string menuLabel = "  Owner: " + owner->getUsername();
        vector<string> menuOptions = {
            "1. Building Management",
            "2. Rent Payment Management",
            "3. Tenant Management",
            "4. Expense Reports",
            "5. Reports and Statistics",
            "0. Logout"
        };

        MenuDisplayer menu(menuLabel, menuOptions);

        int choice = menu.show();

        switch (choice) {
        case 0:
            buildingController->execute();
            break;
        case 1:
            rentPaymentController->execute();
            break;
        case 2:
                tenantController->execute();
            break;
        case 3:
            expenseController->execute();
            break;
        case 4:
                reportsController->execute();
            break;
        case 5:
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
