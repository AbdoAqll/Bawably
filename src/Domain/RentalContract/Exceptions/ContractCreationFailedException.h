#ifndef CONTRACTCREATIONFAILEDEXCEPTION_H
#define CONTRACTCREATIONFAILEDEXCEPTION_H

#include <Shared/DomainException.h>

class ContractCreationFailedException : public DomainException {
public:
    ContractCreationFailedException();
};

#endif //CONTRACTCREATIONFAILEDEXCEPTION_H
