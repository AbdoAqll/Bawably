#include "AddMaintenanceRequestUseCase.h"

#include "Domain/Apartment/Exceptions/ApartmentNotExistException.h"
#include "Domain/Building/Exceptions/BuildingNotExistException.h"

AddMaintenanceRequestUseCase::AddMaintenanceRequestUseCase(shared_ptr<IMaintenanceRequestRepository> rep,
    shared_ptr<IApartmentRepository> apartmentRepo,
    shared_ptr<IBuildingRepository> buildingRepo)
:_maintnenceRequestRepo(rep), _apartmentRepo(apartmentRepo), _buildingRepo(buildingRepo) {
    UseCaseName = "AddMaintenanceRequest";
}

any AddMaintenanceRequestUseCase::execute(const any& params) {
    auto args = any_cast<AddMaintenanceRequestParams>(params);

    if (!_buildingRepo->exists(args.buildingId)) {
        throw(BuildingNotExistException(args.buildingId));
    }

    if (!_apartmentRepo->exists(args.apartmentNumber, args.buildingId)) {
        throw ApartmentNotExistException(to_string(args.apartmentNumber), args.buildingId);
    }

    MaintenanceRequest newRequest(_maintnenceRequestRepo->getNewId(), args.buildingId ,args.apartmentNumber, args.description, args.tenantId);
    _maintnenceRequestRepo->save(newRequest);

    return {};
}

