#ifndef MAINTENANCE_REQUEST_NOTFOUND_EXCEPTION_H
#define MAINTENANCE_REQUEST_NOTFOUND_EXCEPTION_H
#include <exception>

#include "Shared/DomainException.h"

class MaintenanceRequestNotFoundException : public DomainException {
public:
    MaintenanceRequestNotFoundException(int requestId);
};

#endif