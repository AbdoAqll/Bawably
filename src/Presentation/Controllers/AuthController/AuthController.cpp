#include "AuthController.h"
#include "UI/ConsoleUtils.h"
#include "UI/InputForm.h"
#include "UI/MenuDisplayer.h"
#include <iostream>

using namespace std;

AuthController::AuthController(shared_ptr<LoginUseCase> loginUseCase)
    : loginUseCase(loginUseCase) {
}

shared_ptr<User> AuthController::showLoginForm() {
    while (true) {
        ConsoleUtils::clearScreen();

        MenuDisplayer menu("Welcome to Bawably System", vector<string>{
            "1. Login",
            "0. Exit"
            });

        int choice = menu.show();

        switch (choice) {
        case 0: {
            shared_ptr<User> user = performLogin();
            if (user != nullptr) {
                return user;
            }
            break;
        }
        case 1:
        case -1:
            // Exit
            return nullptr;
        }
    }
}

shared_ptr<User> AuthController::performLogin() {
    ConsoleUtils::clearScreen();

    InputForm form("Login");
    form.addTextField("username", "Username", 30, true)
        .addTextField("password", "Password", 30, true);

    FormResult result = form.show();

    if (result.cancelled) {
        return nullptr;
    }

    if (result.submitted) {
        string username = result.get("username");
        string password = result.get("password");

        try {
            LoginParams params{ username, password };
            any loginResult = loginUseCase->execute(params);
            shared_ptr<User> user = any_cast<shared_ptr<User>>(loginResult);

            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::HIGHLIGHT);
            cout << "\n Login successful!" << endl;
            cout << " Welcome, " << user->getUsername() << "!" << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();

            return user;
        }
        catch (const exception& e) {
            ConsoleUtils::clearScreen();
            ConsoleUtils::textattr(Colors::ERR);
            cout << "\n Login failed: " << e.what() << endl;
            ConsoleUtils::textattr(Colors::DEFAULT);
            cout << "\nPress any key to continue...";
            ConsoleUtils::getKey();
        }
    }
    return nullptr;
}
