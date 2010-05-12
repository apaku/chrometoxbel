cmake_minimum_required(VERSION 2.8)
project(chrometoxbel)

set( CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_SOURCE_DIR}/cmake )

# Use RPath for installed stuff
set(CMAKE_SKIP_BUILD_RPATH FALSE)
set(CMAKE_BUILD_WITH_INSTALL_RPATH FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

if(WIN32)
  set( BIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX} CACHE FILEPATH "Install path for binaries" )
else(WIN32)
  set( BIN_INSTALL_DIR ${CMAKE_INSTALL_PREFIX}/bin CACHE FILEPATH "Install path for binaries" )
endif(WIN32)

find_package( Qt4 4.5.0 COMPONENTS QtCore QtXml REQUIRED )
find_package( QJSON REQUIRED )

include_directories( ${QT_INCLUDES} ${QJSON_INCLUDE_DIR} )

add_executable( chrometoxbel main.cpp )
target_link_libraries( chrometoxbel ${QT_QTCORE_LIBRARY} ${QT_QTXML_LIBRARY} ${QJSON_LIBRARIES} )

install( TARGETS chrometoxbel RUNTIME DESTINATION ${BIN_INSTALL_DIR} )
