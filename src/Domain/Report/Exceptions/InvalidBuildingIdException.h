#ifndef INVALIDBUILDINGIDEXCEPTION_H
#define INVALIDBUILDINGIDEXCEPTION_H

#include "../../Shared/DomainException.h"

class InvalidBuildingIdException : public DomainException {
public:
    explicit InvalidBuildingIdException(int buildingId);
};

#endif //INVALIDBUILDINGIDEXCEPTION_H
