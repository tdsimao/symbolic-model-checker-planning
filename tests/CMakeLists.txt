include_directories( BEFORE ../lib/cudd/include)
LINK_DIRECTORIES(../lib/cudd/lib)

# Add executable called "test" that is built from the source "test.cpp".
# The extensions are automatically found.
add_executable (my_test test.cpp)

# Link the executable to the smcp library. Since the Hello library has
# public include directories we will use those link directories when building my_test
target_link_libraries (my_test LINK_PUBLIC smcp cudd gtest gtest_main)


add_definitions(-std=c++11)



include_directories(${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR})
add_executable (runTests smcp_unittest.cc)
target_link_libraries (runTests LINK_PUBLIC smcp cudd pthread gtest gtest_main)
