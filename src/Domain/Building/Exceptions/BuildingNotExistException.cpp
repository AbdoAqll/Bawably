#include "BuildingNotExistException.h"


BuildingNotExistException::BuildingNotExistException(int buildingId) : DomainException("Building with Id " + to_string(buildingId) + " does not exist.") {}
