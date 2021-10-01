macro(core_test test)
    icm_add_doctest_lib_test(${test} core ${ARGN})
endmacro()

core_test(LetterSequence t-LetterSequence.cpp)
core_test(Language t-Language.cpp)
core_test(DictionarySearch t-DictionarySearch.cpp)
core_test(Grid t-Grid.cpp)
core_test(BoardUtils t-BoardUtils.cpp)

# core_test(Scoring t-Scoring.cpp)
