include_directories(".")

file(GLOB_RECURSE SOURCE_FILES ./*)
add_executable(LitmusCompiler ${SOURCE_FILES})

target_link_libraries(LitmusCompiler LibChemistryHelper)
