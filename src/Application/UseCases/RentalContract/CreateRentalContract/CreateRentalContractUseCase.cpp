#include "CreateRentalContractUseCase.h"
#include "Domain/RentalContract/Exceptions/ContractAlreadyExistsException.h"
#include "Domain/Apartment/Exceptions/ApartmentNotExistException.h"
#include "Domain/Apartment/ApartmentStatus.h"

CreateRentalContractUseCase::CreateRentalContractUseCase(
    const shared_ptr<IRentalContractRepository>& rentalContractRepository,
    const shared_ptr<IApartmentRepository>& apartmentRepository,
    const shared_ptr<ITenantRepository>& tenantRepository) {
    _rentalContractRepository = rentalContractRepository;
    _apartmentRepository = apartmentRepository;
    _tenantRepository = tenantRepository;
    UseCaseName = "CreateRentalContract";
}

any CreateRentalContractUseCase::execute(const any& params) {
    auto args = any_cast<CreateRentalContractParams>(params);

    if (!_apartmentRepository->exists(args.apartmentId, args.buildingId)) {
        throw ApartmentNotExistException(to_string(args.apartmentId), args.buildingId);
    }

    if (!_tenantRepository->exists(args.tenantId)) {
        throw DomainException("Tenant with ID " + to_string(args.tenantId) + " does not exist");
    }

    if (_rentalContractRepository->existsActiveContract(args.apartmentId, args.tenantId)) {
        throw ContractAlreadyExistsException(args.apartmentId, args.tenantId);
    }

    auto apartment = _apartmentRepository->findById(args.apartmentId, args.buildingId);
    if (apartment.getStatus() == ApartmentStatus::Rented) {
        throw DomainException("Apartment is already rented");
    }

    static int nextContractId = 1;
    RentalContract contract(nextContractId++, args.buildingId, args.apartmentId, args.tenantId,
        args.monthlyRent, args.startDate);

    if (!_rentalContractRepository->save(contract)) {
        throw DomainException("Failed to create rental contract");
    }

    apartment.setStatus(ApartmentStatus::Rented);
    _apartmentRepository->save(apartment);

    return contract.getContractId();
}
