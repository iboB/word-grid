
icm_add_lib(core CORE
    lib/UnicodeCharFromUtf8.hpp
    lib/UnicodeTolower.hpp
    lib/UnicodeTolower.cpp
    lib/Utf8FromUnicodeChar.hpp

    Types.hpp
    LetterSequence.hpp
    LetterSequenceFromUtf8.hpp
    WordTraits.hpp
    WordMatchSequence.hpp
    BasicLanguage.hpp
    BasicLanguage.cpp
    DictionaryWord.hpp
    Dictionary.hpp
    DictionarySearch.hpp
    DictionarySearch.cpp
    LanguageTypes.hpp
    Language.hpp
    Language.cpp
    LanguageBuilder.hpp
    LanguageBuilder.cpp
    GridElementTraits.hpp
    GridElement.hpp
    GridElement.cpp
    GridCoord.hpp
    GridPath.hpp
    GridPath.cpp
    Grid.hpp
    ScoredWord.hpp
    GridUtils.hpp
    GridUtils.cpp
    ScoreUtils.hpp
    ScoreUtils.cpp

    BasicBoard.hpp
    BoardUtils.hpp
    BoardUtils.cpp

    PRNG.hpp
    PRNG.cpp
)

target_include_directories(core INTERFACE ..)

target_link_libraries(core
    PUBLIC
        itlib
        splat
        huse
)
