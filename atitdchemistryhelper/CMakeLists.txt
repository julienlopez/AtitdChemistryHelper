include_directories(".")

file(GLOB_RECURSE SOURCE_FILES ./*)
add_executable(AtitdChemistryHelper ${SOURCE_FILES})

target_link_libraries(AtitdChemistryHelper LibChemistryHelper)
