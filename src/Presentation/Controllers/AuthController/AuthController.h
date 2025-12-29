#ifndef AUTHCONTROLLER_H
#define AUTHCONTROLLER_H

#include <memory>
#include "Application/UseCases/User/Login/LoginUseCase.h"
#include "Domain/User/User.h"

using namespace std;

class AuthController {
private:
    shared_ptr<LoginUseCase> loginUseCase;

    shared_ptr<User> performLogin();

public:
    explicit AuthController(shared_ptr<LoginUseCase> loginUseCase);

    // Returns the logged in user or nullptr if login failed/cancelled
    shared_ptr<User> showLoginForm();

    ~AuthController() = default;
};

#endif // AUTHCONTROLLER_H
