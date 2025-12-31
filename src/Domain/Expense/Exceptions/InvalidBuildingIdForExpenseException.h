#ifndef INVALIDBUILDINGIDFOREXPENSEEXCEPTION_H
#define INVALIDBUILDINGIDFOREXPENSEEXCEPTION_H

#include "../../Shared/DomainException.h"

class InvalidBuildingIdForExpenseException : public DomainException {
public:
    explicit InvalidBuildingIdForExpenseException(int buildingId);
};

#endif //INVALIDBUILDINGIDFOREXPENSEEXCEPTION_H