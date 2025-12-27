add_executable(Presentation
    main.cpp
    Controllers/UserController.cpp
    Controllers/BuildingController/BuildingController.cpp
    Container/DependencyContainer.cpp
    Controllers/ApartmentController/ApartmentController.cpp
        Controllers/ExpenseController/ExpenseController.cpp
        Controllers/ExpenseController/ExpenseController.h
)

target_include_directories(Presentation PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(Presentation PUBLIC Application Infrastructure Domain)