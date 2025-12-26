add_library(Application STATIC
    UseCases/User/CreateUser/CreateUserUseCase.cpp
    UseCases/User/DeleteUser/DeleteUserUseCase.cpp
        UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h
        UseCases/MaintenanceRequest/AddMaintenanceRequest/AddMaintenanceRequestUseCase.h
        UseCases/MaintenanceRequest/ViewMaintenanceRequests/ViewMaintenanceRequestsUseCase.h
        UseCases/MaintenanceRequest/CloseMaintenanceRequest/CloseMaintenanceRequestUseCase.h
)

target_include_directories(Application PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(Application PUBLIC Domain)