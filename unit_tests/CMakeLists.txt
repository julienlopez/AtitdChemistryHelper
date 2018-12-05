include_directories(".")

include(../cmake/catch.cmake)

file(GLOB_RECURSE SOURCE_FILES ./*)
add_executable(unit_tests ${SOURCE_FILES})

target_link_libraries(unit_tests LibChemistryHelper)

include(../cmake/find_compiler.cmake)
find_compiler()
if(${NOT_WINDOWS} EQUAL 0)
	target_link_libraries(unit_tests optimized Catch2 debug Catch2d)
else()
	target_link_libraries(unit_tests -lCatch2)
endif()
