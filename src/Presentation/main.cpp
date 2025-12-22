#include <iostream>
#include <memory>
#include "Controllers/UserController.h"
#include "Infrastructure/User/Repositories/UserRepository.h"

int main()
{
    // Create dependencies
    auto userRepository = std::make_shared<UserRepository>();
    auto createUserUseCase = std::make_shared<CreateUserUseCase>(userRepository);

    // Create controller
    UserController controller(createUserUseCase);

    int choice = 0;

    while (true)
    {
        controller.displayMenu();
        std::cin >> choice;
        std::cin.ignore(); // Clear newline from input buffer

        if (choice == 1)
        {
            int id;
            std::string name, email;

            std::cout << "\nEnter User ID: ";
            std::cin >> id;
            std::cin.ignore();

            std::cout << "Enter Name: ";
            std::getline(std::cin, name);

            std::cout << "Enter Email: ";
            std::getline(std::cin, email);

            controller.createUser(id, name, email);
        }
        else if (choice == 2)
        {
            std::cout << "Exiting...\n";
            break;
        }
        else
        {
            std::cout << "Invalid choice. Please try again.\n";
        }
    }

    return 0;
}