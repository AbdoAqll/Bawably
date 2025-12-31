#include "InvalidCredentialsException.h"

InvalidCredentialsException::InvalidCredentialsException()
    : DomainException("Invalid username or password") {
}
