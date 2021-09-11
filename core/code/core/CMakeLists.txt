
icm_add_lib(core CORE
    lib/UnicodeCharFromUtf8.hpp
)

target_include_directories(core INTERFACE ..)

target_link_libraries(core
    PUBLIC
        itlib
        splat
    PRIVATE
        ${CMAKE_DL_LIBS}
)
