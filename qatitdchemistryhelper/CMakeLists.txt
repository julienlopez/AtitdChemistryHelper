include_directories(".")

include(../cmake/openssl.cmake)
include(../cmake/qt.cmake)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

file(GLOB_RECURSE SOURCE_FILES ./*)
add_executable(QAtitdChemistryHelper ${SOURCE_FILES})

target_link_libraries(QAtitdChemistryHelper LibChemistryHelper)
target_link_libraries(QAtitdChemistryHelper libssl.lib libcrypto.lib)

foreach(MODULE ${ACH_QT_MODULES})
	target_link_libraries(QAtitdChemistryHelper ${${MODULE}_LIBRARIES})
endforeach()
