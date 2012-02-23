cmake_minimum_required(VERSION 2.6)
project(metasim C CXX)

# Numero de version
set(${PROJECT_NAME}_MAJOR_VERSION 0)
set(${PROJECT_NAME}_MINOR_VERSION 1)
set(${PROJECT_NAME}_PATCH_LEVEL 0)
set(${PROJECT_NAME}_VERSION
        "${${PROJECT_NAME}_MAJOR_VERSION}.${${PROJECT_NAME}_MINOR_VERSION}.${${PROJECT_NAME}_PATCH_LEVEL}")

# set(CMAKE_BUILD_WITH_INSTALL_RPATH TRUE) 
set(CMAKE_INSTALL_RPATH ${CMAKE_INSTALL_PREFIX}/lib)
set(CMAKE_SKIP_BUILD_RPATH  FALSE)
set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

# Compilación en modo Release por defecto
if(NOT DEFINED CMAKE_BUILD_TYPE OR "${CMAKE_BUILD_TYPE}" STREQUAL "")
    set(CMAKE_BUILD_TYPE Release)
endif()

set(CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake)

add_definitions(-Wall)

#
# Dependencies
#

if(UNIX)
    set(Boost_USE_MULTITHREADED OFF)
endif()
find_package(Boost 1.45.0)

if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found!")
else(NOT Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})

    message(STATUS "Boost include directory: ${Boost_INCLUDE_DIRS}")
    message(STATUS "Boost libraries directory: ${Boost_LIBRARY_DIRS}")
endif(NOT Boost_FOUND)

find_package(Qt4)
find_package(Qwt6)
find_package(Boost 1.45.0 
    COMPONENTS serialization regex python system thread)

message(STATUS "Boost libraries: ${Boost_LIBRARIES}")

include_directories(${CMAKE_CURRENT_SOURCE_DIR})

if(QT_FOUND)
    set(QT_USE_QTSCRIPT 1)
    set(QT_USE_QTSCRIPTTOOLS 1)
    include(${QT_USE_FILE})
endif()

if(NOT Qwt6_FOUND)
    message(STATUS "Qwt6 not found! Disabling plotting support!")
else()
    message(STATUS "Qwt6 available at: ${Qwt6_INCLUDE_DIR}")
endif()

add_subdirectory(metasim)

# Opciones de empaquetado
set(CPACK_GENERATOR "TGZ")
set(CPACK_PACKAGE_VERSION_MAJOR ${${PROJECT_NAME}_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${${PROJECT_NAME}_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATCH ${${PROJECT_NAME}_PATCH_LEVEL})
set(CPACK_SOURCE_GENERATOR "TGZ")
include(CPack)

