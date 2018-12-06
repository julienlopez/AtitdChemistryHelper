include_directories(".")

include_directories(../3rd_party)

file(GLOB_RECURSE SOURCE_FILES ./*)
add_executable(unit_tests ${SOURCE_FILES})

target_link_libraries(unit_tests LibChemistryHelper)
