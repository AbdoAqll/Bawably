add_library(Domain STATIC
    User/User.cpp
    Apartment/Apartment.cpp
    Building/Building.cpp
    Expense/Expense.cpp
    MaintenanceRequest/MaintenanceRequest.cpp
    RentalContract/RentalContract.cpp
    RentPayment/RentPayment.cpp
    Tenant/Tenant.cpp
    Shared/DomainException.cpp
    Building/Exceptions/BuildingNotExistException.cpp
    Apartment/Exceptions/ApartmentNotExistException.cpp
    Apartment/Exceptions/ApartmentAlreadyExistsException.cpp
    Apartment/ApartmentStatus.cpp
    RentalContract/Exceptions/RentalContractNotFoundException.cpp
    RentalContract/Exceptions/ContractAlreadyExistsException.cpp
)

# this is to tell the cmake where to look for .h files
# CMAKE_CURRENT_SOURCE_DIR => src/Domain
target_include_directories(Domain PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# PRIVATE => only domain sees its headers
# INTERFACE => Domain can't even see its own headers
