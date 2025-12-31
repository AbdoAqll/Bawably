add_library(Application STATIC
        UseCases/Building/AddBuilding/AddBuildingUseCase.cpp
        UseCases/Building/GetAllBuilding/GetAllBuildingUseCase.cpp
        UseCases/Building/GetBuildingDetails/GetBuildingDetailsUseCase.cpp
        UseCases/Building/IsBuildingExists/IsBuildingExistsUseCase.cpp
        UseCases/Apartment/AddApartment/AddApartmentUseCase.cpp
        UseCases/Apartment/GetAllApartments/GetAllApartmentsUseCase.cpp
        UseCases/Apartment/CheckApartmentStatus/CheckApartmentStatusUseCase.cpp
        UseCases/Apartment/GetApartmentDetails/GetApartmentDetailsUseCase.cpp
        UseCases/Apartment/IsApartmentExists/IsApartmentExistsUseCase.cpp
        UseCases/Apartment/CheckApartmentExistsAndGetId/CheckApartmentExistsAndGetIdUseCase.cpp
        UseCases/MaintenanceRequest/AddMaintenanceRequest/AddMaintenanceRequestUseCase.cpp
        UseCases/MaintenanceRequest/ViewBuildingMaintenanceRequests/ViewBuildingMaintenanceRequestsUseCase.cpp
        UseCases/MaintenanceRequest/ViewApartmentMaintenanceRequests/ViewApartmentMaintenanceRequestsUseCase.cpp
        UseCases/MaintenanceRequest/CloseMaintenanceRequest/CloseMaintenanceRequestUseCase.cpp
        UseCases/MaintenanceRequest/Interfaces/IMaintenanceRequestRepository.h
        UseCases/RentalContract/CreateRentalContract/CreateRentalContractUseCase.cpp
        UseCases/RentalContract/EndRentalContract/EndRentalContractUseCase.cpp
        UseCases/User/Login/LoginUseCase.cpp
        UseCases/User/CreateTenantUser/CreateTenantUserUseCase.cpp
        UseCases/Expense/CreateExpenseUseCase.cpp
        UseCases/Expense/GetExpensesByBuildingUseCase.cpp
        UseCases/Expense/GetTotalExpensesByBuildingAndMonthUseCase.cpp
        UseCases/RentPayment/RecordRentPayment/RecordRentPaymentUseCase.cpp
        UseCases/RentPayment/AddPartialPayment/AddPartialPaymentUseCase.cpp
        UseCases/RentPayment/ViewPaidTenants/ViewPaidTenantsUseCase.cpp
        UseCases/RentPayment/ViewUnpaidOrPartialTenants/ViewUnpaidOrPartialTenantsUseCase.cpp
        UseCases/User/GetAllTenants/GetAllTenantsUseCase.h
        UseCases/User/GetAllTenants/GetAllTenantsUseCase.cpp
        UseCases/User/RemoveTenant/RemoveTenantUseCase.cpp
        UseCases/User/RemoveTenant/RemoveTenantUseCase.h
)
target_include_directories(Application PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(Application PUBLIC Domain)