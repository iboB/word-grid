cmake_minimum_required(VERSION 3.10)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(word-grid)

######################
# warnings
if(MSVC)
    set(WG_WARNING_FLAGS "-D_CRT_SECURE_NO_WARNINGS=1")
else()
    set(WG_WARNING_FLAGS "-Wall -Wextra -Wno-unused-variable")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WG_WARNING_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WG_WARNING_FLAGS}")

######################
# cmake lib
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)
include(src_group)

######################
# subdirectories
add_subdirectory(third_party)

add_subdirectory(core)
add_subdirectory(server)
add_subdirectory(scratch)

enable_testing()
add_subdirectory(test)
