add_library(Application STATIC
    UseCases/User/CreateUser/CreateUserUseCase.cpp
    UseCases/User/DeleteUser/DeleteUserUseCase.cpp
    UseCases/Building/AddBuilding/AddBuildingUseCase.cpp
    UseCases/Building/GetAllBuilding/GetAllBuildingUseCase.cpp
    UseCases/Building/GetBuildingDetails/GetBuildingDetailsUseCase.cpp
    UseCases/Building/IsBuildingExists/IsBuildingExistsUseCase.cpp
    UseCases/Apartment/AddApartment/AddApartmentUseCase.cpp
    UseCases/Apartment/GetAllApartments/GetAllApartmentsUseCase.cpp
    UseCases/Apartment/CheckApartmentStatus/CheckApartmentStatusUseCase.cpp
    UseCases/Apartment/GetApartmentDetails/GetApartmentDetailsUseCase.cpp
    UseCases/Apartment/IsApartmentExists/IsApartmentExistsUseCase.cpp
    UseCases/RentalContract/CreateRentalContract/CreateRentalContractUseCase.cpp
    UseCases/RentalContract/EndRentalContract/EndRentalContractUseCase.cpp
)

target_include_directories(Application PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(Application PUBLIC Domain)