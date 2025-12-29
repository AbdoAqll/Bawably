#include "AddApartmentUseCase.h"

#include <Apartment/Exceptions/ApartmentAlreadyExistsException.h>
#include <UseCases/Building/AddBuilding/AddBuildingUseCase.h>

#include "Building/Exceptions/BuildingNotExistException.h"


AddApartmentUseCase::AddApartmentUseCase(
    const shared_ptr<IApartmentRepository>& apartmentRepository,
    const shared_ptr<IBuildingRepository>& buildingRepository) {
    _apartmentRepository = apartmentRepository;
    _buildingRepository = buildingRepository;
    UseCaseName = "AddApartment";
}

any AddApartmentUseCase::execute(const any &params) {
    auto args = any_cast<AddApartmentParams>(params);

    if (!_buildingRepository->exists(args.buildingId)) {
        throw BuildingNotExistException(args.buildingId);
    }

    Apartment apartment(args.buildingId, args.apartmentNumber);
    if (!_apartmentRepository->save(apartment)) {
        throw ApartmentAlreadyExistsException(apartment.getApartmentNumber(), args.buildingId);
    }

    return {};
}


