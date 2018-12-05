set(ACH_BOOST_ROOT_DIR "" CACHE PATH "Use specific boost folder?")
if(NOT "${ACH_BOOST_ROOT_DIR}" STREQUAL "")
	include_directories("${ACH_BOOST_ROOT_DIR}")
	link_directories("${ACH_BOOST_ROOT_DIR}/stage/lib")
endif()