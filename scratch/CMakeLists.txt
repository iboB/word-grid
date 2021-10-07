add_executable(scratch scratch-b.cpp PlatformUtil.cpp)
target_link_libraries(scratch core ${CMAKE_DL_LIBS})
