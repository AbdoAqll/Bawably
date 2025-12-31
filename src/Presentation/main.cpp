#include <iostream>
#include <memory>
#include "Container/DependencyContainer.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include "Domain/User/User.h"
#include "Domain/User/Owner.h"
#include "Domain/User/TenantUser.h"
#include <string>

using namespace std;

int main() {
    // Initialize console for proper character encoding (box-drawing chars)
    ConsoleUtils::initConsole();
    ConsoleUtils::clearScreen();

    DependencyContainer container;
    auto& authController = *container.getAuthController();
    auto& ownerMenuController = *container.getOwnerMenuController();
    auto& tenantMenuController = *container.getTenantMenuController();
    auto& rentalContractController = *container.getRentalContractController();

    bool running = true;
    while (running) {
        shared_ptr<User> loggedInUser = authController.showLoginForm();
        if (loggedInUser == nullptr) {
            // User chose to exit
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Thank you for using Bawably System!" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            running = false;
            break;
        }

        // Route to appropriate menu based on user role
        if (loggedInUser->getRole() == UserRole::OWNER) {
            // Cast to Owner and show owner menu
            auto owner = dynamic_pointer_cast<Owner>(loggedInUser);
            if (owner) {
                ownerMenuController.execute(owner);
            }
        }
        else if (loggedInUser->getRole() == UserRole::TENANT) {
            // Cast to TenantUser and show tenant menu
            auto tenant = dynamic_pointer_cast<TenantUser>(loggedInUser);
            if (tenant) {
                auto rentalContract = rentalContractController.getContractForTenantId(tenant->getUserId());
                if (rentalContract) {
                    tenantMenuController.execute(tenant, rentalContract);
                }
                else {
                    ConsoleUtils::clearScreen();
                    ConsoleUtils::textattr(Colors::ERR);
                    cout << "\n You have been logged out due to no active rental contract." << endl;
                    ConsoleUtils::textattr(Colors::DEFAULT);
                    cout << "\nPress any key to continue...";
                    ConsoleUtils::getKey();
                }
            }
        }
        // After logout, loop back to login screen
    }

    return 0;
}