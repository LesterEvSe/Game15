cmake_minimum_required(VERSION 3.22)
project(Game15)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

if (WIN32)
    set(QT_DIR "C:/*/${QT_VERSION_MAJOR}*/msvc*/lib/cmake/Qt${QT_VERSION_MAJOR}")

elseif (UNIX AND APPLE)
    execute_process(COMMAND find /usr/local -type d -name "Qt" 2>/dev/null
        OUTPUT_VARIABLE QT_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE)

elseif (UNIX AND NOT APPLE) # Find in Linux file system
    execute_process(COMMAND find /home -type d -path "*Qt/${QT_VERSION_MAJOR}*/*/lib/cmake"
        OUTPUT_VARIABLE QT_DIR
        OUTPUT_STRIP_TRAILING_WHITESPACE)
endif()


if (QT_DIR)
    list(APPEND CMAKE_PREFIX_PATH "${QT_DIR}")
    message(STATUS "Set CMAKE_PREFIX_PATH: ${CMAKE_PREFIX_PATH}")
else()
    message(FATAL_ERROR "Could not find Qt directory")
endif()

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core Gui Widgets Sql)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core Gui Widgets Sql)

include_directories(
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/src
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/include
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/forms

    ${CMAKE_CURRENT_SOURCE_DIR}/logic/src
    ${CMAKE_CURRENT_SOURCE_DIR}/logic/include
)

set(SOURCES
    ${CMAKE_CURRENT_SOURCE_DIR}/main.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/src/game.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/src/menu.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/src/statistics.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/src/acceptresult.cpp

    ${CMAKE_CURRENT_SOURCE_DIR}/logic/src/solver.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logic/src/item.cpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logic/src/database.cpp
)

# This is necessary for moc files,
# otherwise there will be an error!
set(HEADERS
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/include/game.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/include/menu.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/include/statistics.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/include/acceptresult.hpp

    ${CMAKE_CURRENT_SOURCE_DIR}/logic/include/solver.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logic/include/item.hpp
    ${CMAKE_CURRENT_SOURCE_DIR}/logic/include/database.hpp
)

# To display these files in Qt Creator
set(FORMS
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/forms/game.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/forms/menu.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/forms/statistics.ui
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/forms/acceptresult.ui
)

set(ALL_SOURCES
    ${SOURCES}
    ${HEADERS}
    ${FORMS}
    ${CMAKE_CURRENT_SOURCE_DIR}/resource.qrc
)

# Need for Android build
if(${QT_VERSION_MAJOR} GREATER_EQUAL 6)
    qt_add_executable(Game15
        MANUAL_FINALIZATION
        ${ALL_SOURCES}
    )
else()
    if (ANDROID)
        add_library(Game15 SHARED ${ALL_SOURCES})
    else()
        add_executable(Game15 ${ALL_SOURCES})
    endif()
endif()

target_link_libraries(Game15 PRIVATE
    Qt${QT_VERSION_MAJOR}::Core
    Qt${QT_VERSION_MAJOR}::Gui
    Qt${QT_VERSION_MAJOR}::Widgets
    Qt${QT_VERSION_MAJOR}::Sql
)

# To specify where the .ui files are located
set_target_properties(Game15 PROPERTIES AUTOUIC_SEARCH_PATHS
    ${CMAKE_CURRENT_SOURCE_DIR}/graphics/forms
)

# Need for Android build
install(TARGETS Game15
    BUNDLE DESTINATION .
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)

if(QT_VERSION_MAJOR EQUAL 6)
    qt_finalize_executable(Game15)
endif()
