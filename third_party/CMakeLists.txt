add_subdirectory(doctest)

add_library(chobo-shl INTERFACE)
target_include_directories(chobo-shl INTERFACE chobo-shl/include)

add_library(acme INTERFACE)
target_include_directories(acme INTERFACE acme)
