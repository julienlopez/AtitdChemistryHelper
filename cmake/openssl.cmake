set(ACH_OPEN_SSL_ROOT_DIR "" CACHE PATH "Use specific openSSL folder?")
if(NOT "${ACH_OPEN_SSL_ROOT_DIR}" STREQUAL "")
	include_directories("${ACH_OPEN_SSL_ROOT_DIR}/include")
	link_directories("${ACH_OPEN_SSL_ROOT_DIR}/lib")
endif()