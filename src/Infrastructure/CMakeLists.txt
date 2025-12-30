add_library(Infrastructure STATIC
        Building/Repositories/BuildingRepository.cpp
        Apartment/Repositories/InMemoryApartmentRepository.cpp
        MaintenanceRequest/Repositories/InMemoryMaintenanceRequestRepository.cpp
        RentalContract/Repositories/InMemoryRentalContractRepository.cpp
        User/Repositories/InMemoryUserRepository.cpp
        Expense/Repositories/InMemoryExpenseRepository.cpp
)


target_include_directories(Infrastructure PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(Infrastructure PUBLIC Application Domain)
