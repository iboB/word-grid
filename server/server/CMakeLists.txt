set(src)

src_group(server src
    Game.cpp
    Game.hpp
    Universe.cpp
    Universe.hpp
    Player.cpp
    Player.hpp
    PlayerPtr.hpp
    PlayerSet.hpp
    BoardProducer.hpp
)

add_library(server STATIC
    ${src}
)

target_include_directories(server INTERFACE ..)

target_link_libraries(server PUBLIC core)
