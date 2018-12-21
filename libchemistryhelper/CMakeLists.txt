include_directories(".")

include(../cmake/openssl.cmake)

file(GLOB_RECURSE SOURCE_FILES ./*)

add_library(LibChemistryHelper ${SOURCE_FILES})
