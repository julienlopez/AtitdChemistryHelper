include_directories(".")

include(../cmake/openssl.cmake)

file(GLOB_RECURSE SOURCE_FILES ./*)
add_executable(AtitdChemistryHelper ${SOURCE_FILES})

target_link_libraries(AtitdChemistryHelper LibChemistryHelper)
target_link_libraries(AtitdChemistryHelper libssl.lib libcrypto.lib)
