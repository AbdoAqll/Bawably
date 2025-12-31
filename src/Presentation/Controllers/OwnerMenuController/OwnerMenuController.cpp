#include "OwnerMenuController.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include <iostream>

using namespace std;

OwnerMenuController::OwnerMenuController(
    shared_ptr<BuildingController> buildingCtrl,
    shared_ptr<RentPaymentController> rentPaymentCtrl)
    : buildingController(buildingCtrl), rentPaymentController(rentPaymentCtrl) {
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
            "0. Logout"
            // 3 ten man
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
