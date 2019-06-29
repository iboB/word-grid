add_library(doctest INTERFACE)
target_include_directories(doctest INTERFACE .)

add_library(doctest-main STATIC
    doctest/doctest_fwd.h
    doctest/doctest_impl.h
    doctest/doctest.h
    doctest/doctest_main.cpp
)
target_link_libraries(doctest-main PUBLIC doctest)
set_target_properties(doctest-main PROPERTIES FOLDER test)
