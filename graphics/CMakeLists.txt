add_library(graphics
    src/game.cpp
    src/menu.cpp
    src/statistics.cpp
    src/acceptresult.cpp
    
    # This is necessary for moc files,
    # otherwise there will be an error!
    include/game.hpp
    include/menu.hpp
    include/statistics.hpp
    include/acceptresult.hpp
    
    # To display these files in Qt Creator
    forms/game.ui
    forms/menu.ui
    forms/statistics.ui
    forms/acceptresult.ui
)

# To specify where the .ui files are located
set_target_properties(graphics PROPERTIES AUTOUIC_SEARCH_PATHS forms)
target_include_directories(graphics
    PUBLIC include
    ../logic/include
)

target_link_libraries(graphics PRIVATE
    Qt5::Core
    Qt5::Gui
    Qt5::Widgets
    Qt5::Sql
)
