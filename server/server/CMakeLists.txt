set(src
    Board.cpp
    Board.hpp
    Game.cpp
    Game.hpp
    Universe.cpp
    Universe.hpp
    Player.cpp
    Player.hpp
    PlayerPtr.hpp
    PlayerSet.hpp
    BoardProducer.hpp
	BoardProducerPtr.hpp
)

add_library(server STATIC
    ${src}
)

target_include_directories(server INTERFACE ..)

target_link_libraries(server PUBLIC core)
