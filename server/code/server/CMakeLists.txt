
icm_add_lib(server SERVER
    API.h

    Session.hpp
    Session.cpp
)

target_include_directories(server INTERFACE ..)

target_link_libraries(server
    PUBLIC
        core
)
