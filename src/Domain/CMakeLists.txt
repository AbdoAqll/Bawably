add_library(Domain STATIC
    Apartment/Apartment.cpp
    Building/Building.cpp
    Expense/Expense.cpp
    MaintenanceRequest/MaintenanceRequest.cpp
    RentalContract/RentalContract.cpp
    RentPayment/RentPayment.cpp
    Report/MonthlyBuildingReport.cpp
    Report/GlobalBuildingReport.cpp
    Report/Exceptions/InvalidBuildingIdException.cpp
    Report/Exceptions/ReportGenerationFailedException.cpp
    Shared/DomainException.cpp
        Shared/CurrentDate.cpp
    Shared/InvalidMonthException.cpp
    Shared/InvalidYearException.cpp
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
    RentPayment/Exceptions/InvalidPaymentAmountException.cpp
    RentPayment/Exceptions/PaymentCreationFailedException.cpp
    RentPayment/Exceptions/PaymentRecordExistsException.cpp
    RentPayment/Exceptions/PaymentUpdateFailedException.cpp
    Expense/Exceptions/InvalidExpenseAmountException.cpp
    Expense/Exceptions/InvalidExpenseDateException.cpp
    Expense/Exceptions/InvalidBuildingIdForExpenseException.cpp
    Expense/Exceptions/ExpenseNotFoundException.cpp
    Expense/Exceptions/InvalidExpenseCategoryException.cpp
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
