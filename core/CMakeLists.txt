set(src)
src_group(lib src
    lib/UnicodeCharFromUtf8.hpp
)
src_group(core src
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
)
src_group(scorings src
    scorings/Flat.cpp
    scorings/Flat.hpp
    scorings/Length.cpp
    scorings/Length.hpp
    scorings/Scrabble.cpp
    scorings/Scrabble.hpp
)

add_library(core STATIC
    ${src}
)

target_include_directories(core INTERFACE ..)

target_link_libraries(core PUBLIC chobo-shl)
