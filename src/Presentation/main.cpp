#include <iostream>
#include <memory>
#include <string>
#include "Container/DependencyContainer.h"

using namespace std;

int main() {
    DependencyContainer container;
    auto& userController = *container.getUserController();
    auto& buildingController = *container.getBuildingController();
    auto& apartmentController = *container.getApartmentController();
    auto& rentalContractController = *container.getRentalContractController();

    int choice = 0;
    while (true) {
        cout << "\n=== Bawably System ===\n";
        cout << "1. Building Management\n";
        cout << "2. Apartment Management\n";
        cout << "3. Rental Contract Management\n";
        cout << "0. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();
        buildingController.execute();
        if (choice == 1) {

        }
        else if (choice == 2) {
            apartmentController.execute(0);
        }
        else if (choice == 3) {
            rentalContractController.showMenu();
        }
        else if (choice == 0) {
            cout << "Exiting...\n";
            break;
        }
        else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}