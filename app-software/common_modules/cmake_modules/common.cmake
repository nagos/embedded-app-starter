include(FindPackageHandleStandardArgs)
project(PSDC-4230)

set(CMAKE_CXX_STANDARD 14)
set(CMAKE_INCLUDE_CURRENT_DIR ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} ${CMAKE_CURRENT_SOURCE_DIR}/common_modules/cmake_modules)

IF(CMAKE_BUILD_TYPE STREQUAL "Debug")
        SET(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -O3")
        SET(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -O3")
        add_definitions(-DQT_NO_EXCEPTIONS)
ENDIF(CMAKE_BUILD_TYPE STREQUAL "Debug")

find_program(CMAKE_CXX_CPPCHECK_BINARY NAMES cppcheck)
find_package_handle_standard_args(cppcheck REQUIRED_VARS CMAKE_CXX_CPPCHECK_BINARY)

if (cppcheck_FOUND)
    list(
        APPEND CMAKE_CXX_CPPCHECK 
            ${CMAKE_CXX_CPPCHECK_BINARY}
            "--enable=warning,information"
            "--suppress=missingIncludeSystem"
            "--suppress=unmatchedSuppression"
            "--suppress=noValidConfiguration"
            "--suppress=unknownMacro"
            "--suppress=ConfigurationNotChecked"
            "--inconclusive"
            "--force" 
            "--inline-suppr"
            "--quiet"
    )
endif()

find_package(Qt5Network)
find_package(Qt5WebSockets)
find_package(Qt5 COMPONENTS Widgets REQUIRED)
find_package(Qt5SerialPort)
find_package(Qt5Test)
find_package(Tufao1 QUIET)

include_directories(${Qt5Core_INCLUDE_DIRS})
include_directories(${Qt5Network_INCLUDE_DIRS})
include_directories(${Qt5WebSockets_INCLUDE_DIRS})
include_directories(${Qt5Test_INCLUDE_DIRS})
include_directories(${TUFAO_INCLUDE_DIR})
set(CMAKE_POSITION_INDEPENDENT_CODE ON)
set(CMAKE_AUTORCC ON)
enable_testing(true)

if (Tufao1_FOUND)
	add_definitions(-DWITH_TUFAO)
endif (Tufao1_FOUND)

add_subdirectory("common_modules")
