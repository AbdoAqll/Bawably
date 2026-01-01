#ifndef USERNAMEALREADYTAKENEXCEPTION_H
#define USERNAMEALREADYTAKENEXCEPTION_H

#include <Shared/DomainException.h>
#include <string>

class UsernameAlreadyTakenException : public DomainException {
public:
    explicit UsernameAlreadyTakenException(const std::string& username);
};

#endif //USERNAMEALREADYTAKENEXCEPTION_H
