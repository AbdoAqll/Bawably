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

    int choice = 0;
    while(true) {
        cout << "\n=== Bawably System ===\n";
        cout << "1. Building Management\n";
        cout << "2. Exit\n";
        cout << "Enter choice: ";
        cin >> choice;
        cin.ignore();

        if (choice == 1) {
            buildingController.execute();
        } else if (choice == 2) {
            cout << "Exiting...\n";
            break;
        } else {
            cout << "Invalid choice.\n";
        }
    }

    return 0;
}