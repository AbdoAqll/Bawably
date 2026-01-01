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
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Thank you for using Bawably System!" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            running = false;
            break;
        }

        if (loggedInUser->getRole() == UserRole::OWNER) {
            auto owner = dynamic_pointer_cast<Owner>(loggedInUser);
            if (owner) {
                ownerMenuController.execute(owner);
            }
        }
        else if (loggedInUser->getRole() == UserRole::TENANT) {
            auto tenant = dynamic_pointer_cast<TenantUser>(loggedInUser);
            if (tenant) {
                auto rentalContract = rentalContractController.getContractForTenantId(tenant->getUserId());
                if (rentalContract) {
                    tenantMenuController.execute(tenant, rentalContract);
                }
            }
        }
    }

    return 0;
}