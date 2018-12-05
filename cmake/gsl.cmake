set(ACH_GSL_ROOT_DIR "" CACHE PATH "Use specific GSL folder?")
if(NOT "${ACH_GSL_ROOT_DIR}" STREQUAL "")
	include_directories("${ACH_GSL_ROOT_DIR}/include")
endif()