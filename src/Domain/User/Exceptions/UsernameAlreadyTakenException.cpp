#include "UsernameAlreadyTakenException.h"

UsernameAlreadyTakenException::UsernameAlreadyTakenException(const std::string& username)
    : DomainException("Username '" + username + "' is already taken") {
}
