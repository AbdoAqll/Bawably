#include "CheckApartmentStatusUseCase.h"

#include <Apartment/Exceptions/ApartmentNotExistException.h>
#include <Building/Exceptions/BuildingNotExistException.h>

CheckApartmentStatusUseCase::CheckApartmentStatusUseCase(
    const shared_ptr<IApartmentRepository>& apartmentRepository,
    const shared_ptr<IBuildingRepository>& buildingRepository) {
    _apartmentRepository = apartmentRepository;
    _buildingRepository = buildingRepository;
    UseCaseName = "CheckApartmentStatus";
}

any CheckApartmentStatusUseCase::execute(const any& params) {
    auto args = any_cast<CheckApartmentStatusParams>(params);
    int apartmentId = _apartmentRepository->getApartmentIdFromApartmentNumber(args.apartmentNumber, args.buildingId);
    if (!_buildingRepository->exists(args.buildingId)) {
        throw BuildingNotExistException(args.buildingId);
    }

    if (!_apartmentRepository->exists(apartmentId, args.buildingId)) {
        throw ApartmentNotExistException(args.apartmentNumber, args.buildingId);
    }

    Apartment apartment = _apartmentRepository->findById(apartmentId, args.buildingId);

    return apartment.getStatus();
}

