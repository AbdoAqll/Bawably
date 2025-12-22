add_library(Domain STATIC
    User/User.cpp
)

# this is to tell the cmake where to look for .h files
# CMAKE_CURRENT_SOURCE_DIR => src/Domain
target_include_directories(Domain PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}
)

# PRIVATE => only domain sees its headers
# INTERFACE => Domain can't even see its own headers
