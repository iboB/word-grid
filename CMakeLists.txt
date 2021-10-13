cmake_minimum_required(VERSION 3.14 FATAL_ERROR)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

project(word-grid)

######################
# cpm
include(./cpm/get_cpm.cmake)
macro(dep packageName)
    include(./cpm/${packageName}.cmake)
endmacro()

######################
# compiler specific flags: warnings, etc
if(MSVC)
    set(WG_COMPILER_FLAGS "-D_CRT_SECURE_NO_WARNINGS=1 /Zc:__cplusplus /wd4251 /wd4275 /w34100 /permissive-")
else()
    set(WG_COMPILER_FLAGS "-Wall -Wextra")
endif()

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} ${WG_COMPILER_FLAGS}")
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} ${WG_COMPILER_FLAGS}")

######################
# cmake lib
dep(icm)
set(CMAKE_MODULE_PATH
    ${CMAKE_MODULE_PATH}
    ${icm_SOURCE_DIR}
    ${CMAKE_CURRENT_SOURCE_DIR}/cmake
)
include(icm_add_lib)

######################
# other config and packages

find_package(Threads REQUIRED)

dep(doctest)
include(icm_testing)
enable_testing()

# all executables go to bin
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

######################
# packages
dep(splat)
dep(itlib)
dep(xec)
dep(huse)

######################
# subdirectories

add_subdirectory(core)
add_subdirectory(server)
add_subdirectory(scratch)

