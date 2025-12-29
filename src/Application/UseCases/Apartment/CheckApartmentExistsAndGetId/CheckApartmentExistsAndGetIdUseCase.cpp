#include "CheckApartmentExistsAndGetIdUseCase.h"
#include <Building/Exceptions/BuildingNotExistException.h>
#include <Apartment/Exceptions/ApartmentNotExistException.h>

CheckApartmentExistsAndGetIdUseCase::CheckApartmentExistsAndGetIdUseCase(const shared_ptr<IApartmentRepository>& apartmentRepository, const shared_ptr<IBuildingRepository>& buildingRepository) {
    _apartmentRepository = apartmentRepository;
    _buildingRepository = buildingRepository;
    UseCaseName = "IsApartmentExists";
}

any CheckApartmentExistsAndGetIdUseCase::execute(const any& params) {
    auto args = any_cast<CheckApartmentExistsAndGetIdParams>(params);
    int apartmentId = _apartmentRepository->getApartmentIdFromApartmentNumber(args.apartmentNumber, args.buildingId);
    if (!_buildingRepository->exists(args.buildingId)) {
        throw BuildingNotExistException(args.buildingId);
    }

    if (!_apartmentRepository->exists(apartmentId, args.buildingId)) {
        return -1;
    }
    return apartmentId;
}

