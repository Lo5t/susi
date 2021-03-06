
###################################################################################
#
#  Copyright (c) 2014, webvariants GmbH, http://www.webvariants.de
#
#  This file is released under the terms of the MIT license. You can find the
#  complete text in the attached LICENSE file or online at:
#
#  http://www.opensource.org/licenses/mit-license.php
#
#  @author: Tino Rusch (tino.rusch@webvariants.de)
#
###################################################################################

cmake_minimum_required(VERSION 2.8 FATAL_ERROR)

project(susi)

SET(CMAKE_BUILD_TYPE Debug)

set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/dev")

set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)

find_package(POCO REQUIRED PocoFoundation PocoUtil PocoNet)
find_package(SOCI REQUIRED)
find_package(LibLZMA REQUIRED)
find_package(Threads REQUIRED)

#add_subdirectory( ${CMAKE_SOURCE_DIR}/src/plugins )

add_subdirectory( ${CMAKE_SOURCE_DIR}/test/gtest-1.7.0 )
include_directories( ${gtest_SOURCE_DIR}/include ${gtest_SOURCE_DIR} )

set( CMAKE_COLOR_MAKEFILE ON )

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall -g --std=c++11 -fPIC -Os" )

include_directories( ${CMAKE_SOURCE_DIR}/src/headers )
include_directories( ${CMAKE_SOURCE_DIR}/test/gtest-1.7.0/include )
include_directories( ${POCO_INCLUDE_DIR} )
include_directories( ${SOCI_INCLUDE_DIRS} )

file( GLOB SRCFILES ${CMAKE_SOURCE_DIR}/src/sources/**/*.cpp )
file( GLOB TESTFILES ${CMAKE_SOURCE_DIR}/test/*/*.cpp )

file( GLOB HEADERFILES ${CMAKE_SOURCE_DIR}/src/headers/**/*.h )

#easylogging++ defines 
add_definitions(-DELPP_THREAD_SAFE)
add_definitions(-DELPP_STACKTRACE_ON_CRASH)
add_definitions(-DELPP_SYSLOG)
add_definitions(-DELPP_NO_DEFAULT_LOG_FILE)

#LIBRARY
add_library(lib${PROJECT_NAME} SHARED ${SRCFILES} )
set_target_properties(lib${PROJECT_NAME} PROPERTIES OUTPUT_NAME ${PROJECT_NAME})

#SUSI BINARY
add_executable( ${PROJECT_NAME} ${CMAKE_SOURCE_DIR}/src/sources/main.cc )
target_link_libraries(${PROJECT_NAME}
	lib${PROJECT_NAME}
	${CMAKE_THREAD_LIBS_INIT}
	${SOCI_LIBRARY}
	${LIBLZMA_LIBRARIES}
	${POCO_LIBRARIES}
)

#SUSI TESTS
add_executable(${PROJECT_NAME}_test ${CMAKE_SOURCE_DIR}/test/easylogging++_init.cpp ${TESTFILES})
target_link_libraries(${PROJECT_NAME}_test
	lib${PROJECT_NAME}
	${CMAKE_THREAD_LIBS_INIT}
	${SOCI_LIBRARY}
	${LIBLZMA_LIBRARIES}
	${POCO_LIBRARIES}
	gtest
	gtest_main
)

install(TARGETS lib${PROJECT_NAME} LIBRARY DESTINATION "/usr/lib")
install(TARGETS ${PROJECT_NAME} RUNTIME DESTINATION "/usr/bin")
install(DIRECTORY ${CMAKE_SOURCE_DIR}/src/headers/ DESTINATION /usr/include)
