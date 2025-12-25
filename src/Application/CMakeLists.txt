add_library(Application STATIC
    UseCases/User/CreateUser/CreateUserUseCase.cpp
    UseCases/User/DeleteUser/DeleteUserUseCase.cpp
    UseCases/Building/AddBuilding/AddBuildingUseCase.cpp
    UseCases/Building/GetAllBuilding/GetAllBuildingUseCase.cpp
    UseCases/Building/GetBuildingDetails/GetBuildingDetailsUseCase.cpp
    UseCases/Building/IsBuildingExists/IsBuildingExistsUseCase.cpp
)

target_include_directories(Application PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(Application PUBLIC Domain)