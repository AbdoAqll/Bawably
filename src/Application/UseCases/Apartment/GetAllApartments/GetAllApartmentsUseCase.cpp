#include "GetAllApartmentsUseCase.h"

#include <Building/Exceptions/BuildingNotExistException.h>

GetAllApartmentsUseCase::GetAllApartmentsUseCase(
    const shared_ptr<IApartmentRepository> &apartmentRepository,
    const shared_ptr<IBuildingRepository>& buildingRepository) {
    _apartmentRepository = apartmentRepository;
    _buildingRepository = buildingRepository;
    UseCaseName = "GetAllApartments";
}


any GetAllApartmentsUseCase::execute(const any &params) {
    auto args = any_cast<GetAllApartmentArgs>(params);

    if (!_buildingRepository->exists(args.buildingId)) {
        throw BuildingNotExistException(args.buildingId);
    }

    vector<Apartment> apartments = _apartmentRepository->getAll(args.buildingId);

    return apartments;
}
