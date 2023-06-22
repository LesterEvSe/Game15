# If you change the name of the the folder,
# don't forget to look in the graphics CMakeLists.txt!
add_library(logic
    src/solver.cpp
    src/item.cpp
    src/database.cpp
    
    # This is necessary for moc files,
    # otherwise there will be an error!
    include/solver.hpp
    include/item.hpp
    include/database.hpp
)

target_include_directories(logic PUBLIC include)
target_link_libraries(logic PRIVATE
    Qt5::Sql
	Qt5::Core
)
