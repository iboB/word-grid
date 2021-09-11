
icm_add_lib(core CORE
    lib/UnicodeCharFromUtf8.hpp

    Types.hpp
    WordTraits.hpp
    WordMatchSequence.hpp
    DictionaryWord.hpp
    Dictionary.hpp
    Dictionary.cpp
)

target_include_directories(core INTERFACE ..)

target_link_libraries(core
    PUBLIC
        itlib
        splat
    PRIVATE
        ${CMAKE_DL_LIBS}
)
