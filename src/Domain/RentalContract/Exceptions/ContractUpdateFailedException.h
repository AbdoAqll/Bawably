#ifndef CONTRACTUPDATEFAILEDEXCEPTION_H
#define CONTRACTUPDATEFAILEDEXCEPTION_H

#include <Shared/DomainException.h>

class ContractUpdateFailedException : public DomainException {
public:
    explicit ContractUpdateFailedException(int contractId);
};

#endif //CONTRACTUPDATEFAILEDEXCEPTION_H
