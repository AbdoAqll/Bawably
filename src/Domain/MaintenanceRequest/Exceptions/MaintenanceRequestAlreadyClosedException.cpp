#include "MaintenanceRequestAlreadyClosedException.h"


MaintenanceRequestAlreadyClosedException::MaintenanceRequestAlreadyClosedException(int requestId)
    :DomainException("Request with ID: " + to_string(requestId)+ " is already closed"){}
