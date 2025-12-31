#include "LoginUseCase.h"
#include "Domain/User/Exceptions/InvalidCredentialsException.h"

LoginUseCase::LoginUseCase(shared_ptr<IUserRepository> repo)
    : userRepository(repo) {
    UseCaseName = "Login";
}

any LoginUseCase::execute(const any& params) {
    auto loginParams = any_cast<LoginParams>(params);

    shared_ptr<User> user = userRepository->findByCredentials(loginParams.username, loginParams.password);

    if (user == nullptr) {
        throw InvalidCredentialsException();
    }

    return user;
}
