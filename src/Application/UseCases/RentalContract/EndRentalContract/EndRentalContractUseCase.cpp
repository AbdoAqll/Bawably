#include "EndRentalContractUseCase.h"
#include "Domain/RentalContract/Exceptions/RentalContractNotFoundException.h"
#include "Domain/RentalContract/Exceptions/ContractAlreadyTerminatedException.h"
#include "Domain/RentalContract/Exceptions/ContractUpdateFailedException.h"
#include "Domain/Apartment/ApartmentStatus.h"

EndRentalContractUseCase::EndRentalContractUseCase(
    const shared_ptr<IRentalContractRepository>& rentalContractRepository,
    const shared_ptr<IApartmentRepository>& apartmentRepository) {
    _rentalContractRepository = rentalContractRepository;
    _apartmentRepository = apartmentRepository;
    UseCaseName = "EndRentalContract";
}

any EndRentalContractUseCase::execute(const any& params) {
    auto args = any_cast<EndRentalContractParams>(params);

    RentalContract* contract = _rentalContractRepository->findById(args.contractId);
    if (contract == nullptr) {
        throw RentalContractNotFoundException(args.contractId);
    }

    if (!contract->getIsActive()) {
        throw ContractAlreadyTerminatedException(args.contractId);
    }

    contract->terminateContract(args.endDate);

    if (!_rentalContractRepository->update(*contract)) {
        throw ContractUpdateFailedException(args.contractId);
    }

    auto apartment = _apartmentRepository->findById(contract->getApartmentId());
    apartment.setStatus(ApartmentStatus::Vacant);
    _apartmentRepository->save(apartment);

    return true;
}
