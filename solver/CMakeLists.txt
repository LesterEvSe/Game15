add_library(solver
    src/solver.cpp
    src/item.cpp
    
    # This is necessary for moc files,
    # otherwise there will be an error!
    include/solver.hpp
    include/item.hpp
)

target_include_directories(solver PUBLIC include)
