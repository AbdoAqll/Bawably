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
    Apartment/ApartmentStatus.cpp
        MaintenanceRequest/Exceptions/MaintenanceRequestAlreadyClosedException.cpp
        MaintenanceRequest/Exceptions/MaintenanceRequestNotFoundException.cpp
    RentalContract/Exceptions/RentalContractNotFoundException.cpp
    RentalContract/Exceptions/ContractAlreadyExistsException.cpp
    User/User.cpp
    User/Owner.cpp
    User/TenantUser.cpp
)

# this is to tell the cmake where to look for .h files
# CMAKE_CURRENT_SOURCE_DIR => src/Domain
target_include_directories(Domain PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# PRIVATE => only domain sees its headers
# INTERFACE => Domain can't even see its own headers
