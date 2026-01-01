#ifndef CONTRACTALREADYEXISTSEXCEPTION_H
#define CONTRACTALREADYEXISTSEXCEPTION_H

#include <Shared/DomainException.h>
#include <string>

class ContractAlreadyExistsException : public DomainException {
public:
    explicit ContractAlreadyExistsException(int apartmentId, int tenantId);
};

#endif //CONTRACTALREADYEXISTSEXCEPTION_H
