cmake_minimum_required(VERSION 3.22)
project(Game15)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


# Find in Linux file system
if (UNIX AND NOT APPLE)
	execute_process(COMMAND find /home -type d -path "*Qt/5*/*/lib/cmake"
		OUTPUT_VARIABLE QT_DIR
		OUTPUT_STRIP_TRAILING_WHITESPACE)

	if (QT_DIR)
		list(APPEND CMAKE_PREFIX_PATH "${QT_DIR}")
		message(STATUS "Set CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
	else()
		message(FATAL_ERROR "Could not find Qt directory")
	endif()
endif()

find_package(Qt5 COMPONENTS Core Gui Widgets REQUIRED)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/src
    ${CMAKE_CURRENT_SOURCE_DIR}/include
    ${CMAKE_CURRENT_SOURCE_DIR}/forms
)

set(SOURCES
	${CMAKE_CURRENT_SOURCE_DIR}/src/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/src/menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
)

set(HEADERS
	${CMAKE_CURRENT_SOURCE_DIR}/include/game.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/include/menu.hpp
)

set(FORMS
	${CMAKE_CURRENT_SOURCE_DIR}/forms/game.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/forms/menu.ui
)

set(QRC ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc)


add_executable(Game15 ${SOURCES} ${HEADERS} ${FORMS} ${QRC})

target_link_libraries(Game15 PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
)

# To specify where the .ui files are located
set_target_properties(Game15 PROPERTIES AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/forms
)
