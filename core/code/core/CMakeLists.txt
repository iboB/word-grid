
icm_add_lib(core CORE
    lib/UnicodeCharFromUtf8.hpp
    lib/UnicodeTolower.hpp
    lib/UnicodeTolower.cpp

    Types.hpp
    LetterSequence.hpp
    LetterSequenceFromUtf8.hpp
    WordTraits.hpp
    WordMatchSequence.hpp
    DictionaryWord.hpp
    Dictionary.hpp
    LanguageTypes.hpp
    Language.hpp
    Language.cpp
    LanguageBuilder.hpp
    LanguageBuilder.cpp
    GridElementTraits.hpp
    GridElement.hpp
    GridElement.cpp
)

target_include_directories(core INTERFACE ..)

target_link_libraries(core
    PUBLIC
        itlib
        splat
    PRIVATE
        ${CMAKE_DL_LIBS}
)
