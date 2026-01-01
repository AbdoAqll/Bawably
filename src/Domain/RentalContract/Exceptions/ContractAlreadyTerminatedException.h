#ifndef CONTRACTALREADYTERMINATEDEXCEPTION_H
#define CONTRACTALREADYTERMINATEDEXCEPTION_H

#include <Shared/DomainException.h>

class ContractAlreadyTerminatedException : public DomainException {
public:
    explicit ContractAlreadyTerminatedException(int contractId);
};

#endif //CONTRACTALREADYTERMINATEDEXCEPTION_H
