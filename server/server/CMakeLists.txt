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

src_group(exec src
    exec/ExecutionContext.hpp
    exec/ExecutorBase.cpp
    exec/ExecutorBase.hpp
    exec/TaskExecutor.cpp
    exec/TaskExecutor.hpp
    exec/ThreadExecution.cpp
    exec/ThreadExecution.hpp
)

add_library(server STATIC
    ${src}
)

target_include_directories(server INTERFACE ..)

target_link_libraries(server PUBLIC core)
