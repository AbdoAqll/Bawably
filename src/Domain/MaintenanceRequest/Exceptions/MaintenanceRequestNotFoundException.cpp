#include "Shared/DomainException.h"

MaintenanceRequestNotFoundException::MaintenanceRequestNotFoundException(int requestId)
    :DomainException("There is no maintenance request with id " + to_string(requestId))
{}