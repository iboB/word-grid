macro(add_lib_test test lib)
    set(tname test-${lib}-${test})
    add_executable(${tname} ${ARGN})
    target_link_libraries(${tname} doctest-main ${lib})
    set_target_properties(${tname} PROPERTIES FOLDER test)
    add_test(NAME ${test} COMMAND $<TARGET_FILE:${tname}>)
endmacro()

macro(add_core_test test)
    add_lib_test(${test} core ${ARGN})
endmacro()

add_core_test(LetterSequence t-LetterSequence.cpp)
add_core_test(Grid t-Grid.cpp)
add_core_test(Dictionary t-Dictionary.cpp)
add_core_test(Scoring t-Scoring.cpp)

macro(add_server_test test)
    add_lib_test(${test} server ${ARGN})
endmacro()

add_server_test(TaskExecutor t-TaskExecutor.cpp)
add_server_test(TaskScheduling t-TaskScheduling.cpp)

