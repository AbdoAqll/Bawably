#include "GetApartmentDetailsUseCase.h"
#include <Apartment/Exceptions/ApartmentNotExistException.h>
#include <Building/Exceptions/BuildingNotExistException.h>

GetApartmentDetailsUseCase::GetApartmentDetailsUseCase(
    const shared_ptr<IApartmentRepository> &apartmentRepository,
    const shared_ptr<IBuildingRepository> &buildingRepository) {
    _apartmentRepository = apartmentRepository;
    _buildingRepository = buildingRepository;
    UseCaseName = "GetApartmentDetails";
}

any GetApartmentDetailsUseCase::execute(const any &params) {
    auto args = any_cast<GetApartmentDetailsParams>(params);
    int apartmentId = _apartmentRepository->getApartmentIdFromApartmentNumber(args.aprtmentNumber);
    if (!_buildingRepository->exists(args.buildingId)) {
        throw BuildingNotExistException(args.buildingId);
    }

    if (!_apartmentRepository->exists(apartmentId, args.buildingId)) {
        throw ApartmentNotExistException(args.aprtmentNumber, args.buildingId);
    }

    Apartment apartment = _apartmentRepository->findById(apartmentId, args.buildingId);

    return apartment;
}

