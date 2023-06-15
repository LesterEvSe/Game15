# If you change the name of the library and the folder,
# don't forget to look in the graphics CMakeLists.txt!
add_library(logic
    src/solver.cpp
    src/item.cpp
    
    # This is necessary for moc files,
    # otherwise there will be an error!
    include/solver.hpp
    include/item.hpp
)

target_include_directories(logic PUBLIC include)
