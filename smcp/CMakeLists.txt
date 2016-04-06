
# Create a library called "smcp" which includes the source file "smcp.cc".
add_library (smcp smcp.cc)

target_include_directories (smcp PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})
include_directories(../lib/cudd/include)


add_definitions(-std=c++11)