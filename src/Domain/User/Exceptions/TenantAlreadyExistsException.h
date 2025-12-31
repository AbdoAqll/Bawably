#ifndef TENANTALREADYEXISTSEXCEPTION_H
#define TENANTALREADYEXISTSEXCEPTION_H

#include "../../Shared/DomainException.h"
#include <string>

class TenantAlreadyExistsException : public DomainException {
public:
    explicit TenantAlreadyExistsException(const std::string& nationalId);
};

#endif //TENANTALREADYEXISTSEXCEPTION_H
