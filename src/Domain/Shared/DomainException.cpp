#include "DomainException.h"

DomainException::DomainException(const string &message) {
    _message = message;
}

const char *DomainException::what() const noexcept {
    return _message.c_str();
}

