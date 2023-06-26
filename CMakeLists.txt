cmake_minimum_required(VERSION 3.22)
project(Game15)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
	execute_process(COMMAND dir /B /AD /S "C:\\Path\\to\\Qt\\*\\*\\lib\\cmake" OUTPUT_VARIABLE QT_DIR)
	string(REGEX REPLACE "\n$" "" QT_DIR "${QT_DIR}")
endif()

if (UNIX AND APPLE)
	execute_process(COMMAND find /usr/local -type d -name "Qt" 2>/dev/null
		OUTPUT_VARIABLE QT_DIR
		OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()

# Find in Linux file system
if (UNIX AND NOT APPLE)
    execute_process(COMMAND find /home -type d -path "*Qt/5*/*/lib/cmake"
        OUTPUT_VARIABLE QT_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()



if (QT_DIR)
	list(APPEND CMAKE_PREFIX_PATH "${QT_DIR}")
	message(STATUS "Set CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
else()
	message(FATAL_ERROR "Could not find Qt directory")
endif()


find_package(Qt5 COMPONENTS Core Gui Widgets Sql REQUIRED)

add_subdirectory(graphics)
add_subdirectory(logic)
add_executable(Game15
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc
)

target_link_libraries(Game15 PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Sql
    graphics
    logic
)
