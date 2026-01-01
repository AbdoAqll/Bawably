#ifndef INVALIDCREDENTIALSEXCEPTION_H
#define INVALIDCREDENTIALSEXCEPTION_H

#include <Shared/DomainException.h>

class InvalidCredentialsException : public DomainException {
public:
    InvalidCredentialsException();
};

#endif //INVALIDCREDENTIALSEXCEPTION_H
