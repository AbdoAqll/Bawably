#include <iostream>
#include <memory>
#include "Container/DependencyContainer.h"
#include "UI/ConsoleUtils.h"
#include "UI/MenuDisplayer.h"
#include <string>

using namespace std;

int main() {
    // Initialize console for proper character encoding (box-drawing chars)
    ConsoleUtils::initConsole();
    ConsoleUtils::clearScreen();

    DependencyContainer container;
    auto& buildingController = *container.getBuildingController();

    bool running = true;
    while (running) {

        std::vector<std::string> menuItems = {
            "1. Building Management",
            "0. Exit System"
        };
        MenuDisplayer menu("Bawably System", menuItems);
        int choice = menu.show();

        switch (choice) {
        case 0:
            buildingController.execute();
            break;
        case 1:
        case -1:
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Thank you for using Bawably System!" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            running = false;
            break;
        }
    }

    return 0;
}