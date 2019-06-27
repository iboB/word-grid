set(src)
src_group(grid src
    Grid.cpp
    Grid.h
)

add_library(core STATIC
    ${src}
)

target_include_directories(core INTERFACE ..)

target_link_libraries(core PUBLIC chobo-shl)
