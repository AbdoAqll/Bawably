#include "InvalidBuildingIdForExpenseException.h"

InvalidBuildingIdForExpenseException::InvalidBuildingIdForExpenseException(int buildingId)
    : DomainException("Invalid building ID for expense: " + std::to_string(buildingId) + ". Building ID must be greater than 0") {
}