
icm_add_lib(server SERVER
    API.h

    util/LoadLanguageFromDir.hpp
    util/LoadLanguageFromDir.cpp

    PlatformUtil.hpp
    PlatformUtil.cpp

    Session.hpp
    Session.cpp
)

target_include_directories(server INTERFACE ..)

target_link_libraries(server
    PUBLIC
        core
    PRIVATE
        ${CMAKE_DL_LIBS}
)
