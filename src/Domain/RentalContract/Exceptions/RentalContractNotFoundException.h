#ifndef RENTALCONTRACTNOTFOUNDEXCEPTION_H
#define RENTALCONTRACTNOTFOUNDEXCEPTION_H

#include <Shared/DomainException.h>
#include <string>

class RentalContractNotFoundException : public DomainException {
public:
    explicit RentalContractNotFoundException(int contractId);
};

#endif //RENTALCONTRACTNOTFOUNDEXCEPTION_H
