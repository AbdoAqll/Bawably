add_library(Application STATIC
    UseCases/User/CreateUser/CreateUserUseCase.cpp
    UseCases/User/DeleteUser/DeleteUserUseCase.cpp
)

target_include_directories(Application PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(Application PUBLIC Domain)