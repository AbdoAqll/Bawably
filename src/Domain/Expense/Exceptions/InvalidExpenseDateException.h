#ifndef INVALIDEXPENSEDATEEXCEPTION_H
#define INVALIDEXPENSEDATEEXCEPTION_H

#include <Shared/DomainException.h>

class InvalidExpenseDateException : public DomainException {
public:
    explicit InvalidExpenseDateException(const std::string message);
};

#endif //INVALIDEXPENSEDATEEXCEPTION_H