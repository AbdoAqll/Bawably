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

    if (_rentalContractRepository->existsActiveContract(args.apartmentId, args.tenantId)) {
        throw ContractAlreadyExistsException(args.apartmentId, args.tenantId);
    }

    if (apartment.getStatus() == ApartmentStatus::Rented) {
        throw ApartmentAlreadyRentedException(args.apartmentId);
    }

    static int nextContractId = 1;
    RentalContract contract(nextContractId++, args.apartmentId, args.tenantId,
        args.monthlyRent, args.startDate);

    if (!_rentalContractRepository->save(contract)) {
        throw ContractCreationFailedException();
    }

    apartment.setStatus(ApartmentStatus::Rented);
    _apartmentRepository->save(apartment);

    return contract.getContractId();
}
