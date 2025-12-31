#include "CreateRentalContractUseCase.h"
#include "Domain/RentalContract/Exceptions/ContractAlreadyExistsException.h"
#include "Domain/RentalContract/Exceptions/ContractCreationFailedException.h"
#include "Domain/Apartment/Exceptions/ApartmentNotExistException.h"
#include "Domain/Apartment/Exceptions/ApartmentAlreadyRentedException.h"
#include "Domain/Apartment/ApartmentStatus.h"
#include "Domain/User/Exceptions/TenantNotExistException.h"

CreateRentalContractUseCase::CreateRentalContractUseCase(
    const shared_ptr<IRentalContractRepository>& rentalContractRepository,
    const shared_ptr<IApartmentRepository>& apartmentRepository,
    const shared_ptr<IUserRepository>& userRepository) {
    _rentalContractRepository = rentalContractRepository;
    _apartmentRepository = apartmentRepository;
    _userRepository = userRepository;
    UseCaseName = "CreateRentalContract";
}

any CreateRentalContractUseCase::execute(const any& params) {
    auto args = any_cast<CreateRentalContractParams>(params);

    // Get the apartment to validate it exists
    Apartment apartment = _apartmentRepository->findById(args.apartmentId);

    if (!_userRepository->tenantUserExists(args.tenantId)) {
        throw TenantNotExistException(args.tenantId);
    }

    // Check if this tenant already has an active contract (apartment transfer scenario)
    RentalContract* existingContract = _rentalContractRepository->findActiveByTenant(args.tenantId);
    bool isTransfer = (existingContract != nullptr);
    int previousApartmentId = 0;

    if (isTransfer) {
        // If tenant has active contract and trying to rent same apartment, throw error
        if (existingContract->getApartmentId() == args.apartmentId) {
            throw ContractAlreadyExistsException(args.apartmentId, args.tenantId);
        }

        // Store previous apartment ID for transfer
        previousApartmentId = existingContract->getApartmentId();

        // End the previous contract
        existingContract->setActive(false);
        _rentalContractRepository->update(*existingContract);

        // Set previous apartment status back to Vacant
        Apartment previousApartment = _apartmentRepository->findById(previousApartmentId);
        previousApartment.setStatus(ApartmentStatus::Vacant);
        _apartmentRepository->save(previousApartment);
    }
    else {
        // For new tenants, check if apartment is already rented
        if (apartment.getStatus() == ApartmentStatus::Rented) {
            throw ApartmentAlreadyRentedException(args.apartmentId);
        }
    }

    static int nextContractId = 1;
    RentalContract contract(nextContractId++, args.apartmentId, args.tenantId,
        args.monthlyRent, args.startDate);

    if (!_rentalContractRepository->save(contract)) {
        throw ContractCreationFailedException();
    }

    // Set new apartment status to Rented
    apartment.setStatus(ApartmentStatus::Rented);
    _apartmentRepository->save(apartment);

    // Prepare result with transfer information
    CreateRentalContractResult result;
    result.contractId = contract.getContractId();
    result.isTransfer = isTransfer;
    result.previousApartmentId = previousApartmentId;

    if (isTransfer) {
        result.message = "TRANSFER COMPLETED: Tenant moved from Apartment " +
            to_string(previousApartmentId) + " to Apartment " +
            to_string(args.apartmentId) + ". Previous contract has been terminated.";
    }
    else {
        result.message = "New rental contract created successfully.";
    }

    return result;
}
