#include <iostream>
#include <memory>
#include "Container/DependencyContainer.h"
#include <string>

using namespace std;

int main()
{
    DependencyContainer container;
    auto& userController = *container.getUserController();
    auto& buildingController = *container.getBuildingController();
    auto& apartmentController = *container.getApartmentController();
    auto& maintenanceRequestController = *container.getMaintenanceRequestController();

    int choice = 0;
    while(true) {
        cout << "\n=== Bawably System ===\n";
        cout << "1. Building Management\n";
        cout << "2. Apartment Management\n";
        cout << "3. Maintenance Management\n";
        cout << "4. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            buildingController.execute();
        } else if (choice == 2) {
            // note here i used fixed building id = 0
            // because there is not context switch between buildings tell not
            // will be fixed in the future if the context switch exists.
            apartmentController.execute(0);
        } else if (choice == 3) {
            maintenanceRequestController.execute();
        } else if (choice == 4) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}