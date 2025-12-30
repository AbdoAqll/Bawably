#include "LoginUseCase.h"
#include <stdexcept>

LoginUseCase::LoginUseCase(shared_ptr<IUserRepository> repo)
    : userRepository(repo) {
    UseCaseName = "Login";
}

any LoginUseCase::execute(const any& params) {
    LoginParams loginParams = any_cast<LoginParams>(params);

    shared_ptr<User> user = userRepository->findByCredentials(
        loginParams.username,
        loginParams.password
    );

    if (user == nullptr) {
        throw runtime_error("Invalid username or password");
    }

    return user;
}
