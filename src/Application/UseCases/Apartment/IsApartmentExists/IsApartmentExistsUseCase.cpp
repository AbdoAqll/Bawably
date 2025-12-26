#include "IsApartmentExistsUseCase.h"
#include <Building/Exceptions/BuildingNotExistException.h>
IsApartmentExistsUseCase::IsApartmentExistsUseCase(const shared_ptr<IApartmentRepository> &apartmentRepository, const shared_ptr<IBuildingRepository> &buildingRepository) {
    _apartmentRepository = apartmentRepository;
    _buildingRepository = buildingRepository;
    UseCaseName = "IsApartmentExists";
}

any IsApartmentExistsUseCase::execute(const any &params) {
    auto args = any_cast<IsApartmentExistsParams>(params);
    int apartmentId = _apartmentRepository->getApartmentIdFromApartmentNumber(args.apartmentNumber);
    if (!_buildingRepository->exists(args.buildingId)) {
        throw BuildingNotExistException(args.buildingId);
    }

    if (!_apartmentRepository->exists(apartmentId, args.buildingId)) {
        return false;
    }
    return true;
}

