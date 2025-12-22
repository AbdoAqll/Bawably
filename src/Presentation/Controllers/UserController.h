#ifndef USER_CONTROLLER_H
#define USER_CONTROLLER_H

#include "Application/UseCases/User/CreateUser/CreateUserUseCase.h"
#include <memory>
#include <iostream>
#include <string>

class UserController
{
private:
    std::shared_ptr<CreateUserUseCase> createUserUseCase;

public:
    UserController(std::shared_ptr<CreateUserUseCase> useCase)
        : createUserUseCase(useCase) {}

    void createUser(int id, const std::string &name, const std::string &email)
    {
        bool success = createUserUseCase->execute(id, name, email);

        if (success)
        {
            std::cout << "User created successfully!\n";
            std::cout << "ID: " << id << "\n";
            std::cout << "Name: " << name << "\n";
            std::cout << "Email: " << email << "\n";
        }
        else
        {
            std::cout << "Failed to create user.\n";
        }
    }

    void displayMenu()
    {
        std::cout << "\n=== User Management System ===\n";
        std::cout << "1. Create User\n";
        std::cout << "2. Exit\n";
        std::cout << "Enter your choice: ";
    }
};

#endif // USER_CONTROLLER_H
