#ifndef NOACTIVECONTRACTEXCEPTION_H
#define NOACTIVECONTRACTEXCEPTION_H

#include <Shared/DomainException.h>

class NoActiveContractException : public DomainException {
public:
    explicit NoActiveContractException(int tenantId);
};

#endif //NOACTIVECONTRACTEXCEPTION_H
