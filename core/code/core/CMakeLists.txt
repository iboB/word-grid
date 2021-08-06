
icm_add_lib(core CORE
    lib/UnicodeCharFromUtf8.hpp
    lib/PlatformUtil.cpp
    lib/PlatformUtil.hpp

    Types.hpp
    LetterSequence.hpp
    Word.hpp
    WordTraits.hpp
    WordElement.hpp
    WordElement.cpp
    WordElementTraits.hpp
    Dictionary.cpp
    Dictionary.hpp
    DictionarySearch.hpp
    Grid.cpp
    Grid.hpp
    GridCoord.hpp
    Scoring.hpp
    Scoring.cpp
    ScoredDictionary.cpp
    ScoredDictionary.hpp
    ScoredWord.hpp
    Board.cpp
    Board.hpp
    BoardUtils.cpp
    BoardUtils.hpp
)

target_include_directories(core INTERFACE ..)

target_link_libraries(core PUBLIC
    itlib
    splat
    ${CMAKE_DL_LIBS}
)
