cmake_minimum_required(VERSION 3.2)
project(AtitdChemistryHelper)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
add_definitions("-DNOMINMAX")

if(ENABLE_COVERAGE STREQUAL "ON")
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} --coverage -fprofile-arcs -ftest-coverage -O0")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} --coverage -fprofile-arcs")
endif()

include(cmake/find_compiler.cmake)
set(NOT_VISUAL_STUDIO 0)
find_compiler()
if(${NOT_WINDOWS} EQUAL 0)
else()
	set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -pthread")
	set(CMAKE_EXE_LINKER_FLAGS "${CMAKE_EXE_LINKER_FLAGS} -ldl")
endif()


include_directories(.)
include_directories(3rd_party/range)

include(cmake/boost.cmake)
include(cmake/gsl.cmake)

add_subdirectory(libchemistryhelper)
add_subdirectory(unit_tests)
add_subdirectory(atitdchemistryhelper)
add_subdirectory(litmuscompiler)
add_subdirectory(qatitdchemistryhelper)
