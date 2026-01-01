//
// Created by Mazen on 12/27/2025.
//

#ifndef MAINTENANCE_REQUEST_ALREADY_CLOSED_EXCEPTION_H
#define MAINTENANCE_REQUEST_ALREADY_CLOSED_EXCEPTION_H
#include <Shared/DomainException.h>

class MaintenanceRequestAlreadyClosedException : public DomainException {
public:
    explicit MaintenanceRequestAlreadyClosedException(int requestId);
};

#endif