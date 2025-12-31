add_library(Domain STATIC
    Apartment/Apartment.cpp
    Building/Building.cpp
    Expense/Expense.cpp
    MaintenanceRequest/MaintenanceRequest.cpp
    RentalContract/RentalContract.cpp
    RentPayment/RentPayment.cpp
    Shared/DomainException.cpp
        Shared/CurrentDate.cpp
    Building/Exceptions/BuildingNotExistException.cpp
    Apartment/Exceptions/ApartmentNotExistException.cpp
    Apartment/Exceptions/ApartmentAlreadyExistsException.cpp
    Apartment/Exceptions/ApartmentAlreadyRentedException.cpp
    Apartment/ApartmentStatus.cpp
        MaintenanceRequest/Exceptions/MaintenanceRequestAlreadyClosedException.cpp
        MaintenanceRequest/Exceptions/MaintenanceRequestNotFoundException.cpp
    RentalContract/Exceptions/RentalContractNotFoundException.cpp
    RentalContract/Exceptions/ContractAlreadyExistsException.cpp
    RentalContract/Exceptions/ContractAlreadyTerminatedException.cpp
    RentalContract/Exceptions/ContractCreationFailedException.cpp
    RentalContract/Exceptions/ContractUpdateFailedException.cpp
    RentalContract/Exceptions/NoActiveContractException.cpp
    RentPayment/Exceptions/InvalidMonthException.cpp
    RentPayment/Exceptions/InvalidYearException.cpp
    RentPayment/Exceptions/InvalidPaymentAmountException.cpp
    RentPayment/Exceptions/PaymentCreationFailedException.cpp
    RentPayment/Exceptions/PaymentRecordExistsException.cpp
    RentPayment/Exceptions/PaymentUpdateFailedException.cpp
    User/User.cpp
    User/Owner.cpp
    User/TenantUser.cpp
    User/Exceptions/TenantNotExistException.cpp
    User/Exceptions/TenantAlreadyExistsException.cpp
    User/Exceptions/UsernameAlreadyTakenException.cpp
    User/Exceptions/InvalidCredentialsException.cpp
    User/Exceptions/TenantUserCreationFailedException.cpp
)

# this is to tell the cmake where to look for .h files
# CMAKE_CURRENT_SOURCE_DIR => src/Domain
target_include_directories(Domain PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# PRIVATE => only domain sees its headers
# INTERFACE => Domain can't even see its own headers
