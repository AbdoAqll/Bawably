#include "InvalidBuildingIdException.h"
#include <string>

InvalidBuildingIdException::InvalidBuildingIdException(int buildingId)
    : DomainException("Invalid building ID: " + std::to_string(buildingId) + ". Building ID must be >= 0.") {
}
