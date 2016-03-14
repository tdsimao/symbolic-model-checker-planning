# Create a library called "smcp" which includes the source file "smcp.cxx".
# The extension is already found. Any number of sources could be listed here.
add_library (smcp smcp.cpp)


# Make sure the compiler can find include files for our Hello library
# when other libraries or executables link to Hello


target_include_directories (smcp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})


include_directories( BEFORE ../lib/cudd/include)


