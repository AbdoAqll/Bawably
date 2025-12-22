add_library(Infrastructure STATIC
    User/Repositories/UserRepository.cpp
)

target_include_directories(Infrastructure PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/..
)

target_link_libraries(Infrastructure PUBLIC Application Domain)
