macro(core_test test)
    icm_add_doctest_lib_test(${test} core ${ARGN})
endmacro()

core_test(LetterSequence t-LetterSequence.cpp)
core_test(Grid t-Grid.cpp)
core_test(Dictionary t-Dictionary.cpp)
core_test(Scoring t-Scoring.cpp)
