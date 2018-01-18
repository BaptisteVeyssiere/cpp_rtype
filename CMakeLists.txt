cmake_minimum_required(VERSION 3.0.2)

set( CMAKE_CXX_FLAGS  "-DBOOST_ASIO_SEPARATE_COMPILATION -DBOOST_ASIO_STANDALONE -DBOOST_DATE_TIME_NO_LIB -DBOOST_REGEX_NO_LIB" )
set( CMAKE_CXX_STANDARD 17 )
if (UNIX)
	set(BOOST_DIR ${PROJECT_SOURCE_DIR}/deps/boost)

	include_directories("deps/boost")
	link_directories("deps/boost/stage/lib")

	execute_process(COMMAND "./bootstrap.sh"
		WORKING_DIRECTORY ${BOOST_DIR}
		RESULT_VARIABLE result
		OUTPUT_VARIABLE err)

	MESSAGE(STATUS "bootstrap:${result}: ${err}" )

	execute_process(COMMAND "./b2" "--with-system"
  		WORKING_DIRECTORY ${BOOST_DIR}
  		RESULT_VARIABLE result
  		OUTPUT_VARIABLE err)

	MESSAGE(STATUS "b2:${result}: ${err}" )

endif (UNIX)

if (WIN32)
	set(BOOST_DIR ${PROJECT_SOURCE_DIR}\\deps\\boost)

	include_directories("deps\\boost")
	link_directories("deps\\boost\\stage\\lib")

	execute_process(COMMAND "bootstrap.bat"
		WORKING_DIRECTORY ${BOOST_DIR}
		RESULT_VARIABLE result
		OUTPUT_VARIABLE err)
	MESSAGE(STATUS "bootstrap:${result}: ${err}" )

	execute_process(COMMAND "b2" "--with-system"
  		WORKING_DIRECTORY ${BOOST_DIR}
  		RESULT_VARIABLE result
  		OUTPUT_VARIABLE err)

	MESSAGE(STATUS "b2:${result}: ${err}" )

endif (WIN32)

add_subdirectory(server)
add_subdirectory(client)
