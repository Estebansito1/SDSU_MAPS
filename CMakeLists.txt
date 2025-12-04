cmake_minimum_required(VERSION 3.10)

# New project name
project(SDSU_MAPS)

set(CMAKE_CXX_STANDARD 17)

include_directories(src)

find_package(SFML 2.5 COMPONENTS graphics window system REQUIRED)

# Executable renamed as well
add_executable(SDSU_MAPS
        main.cpp
        src/Building.cpp
        src/Graph.cpp
        src/UI.cpp
)

# Link libraries with the new name
target_link_libraries(SDSU_MAPS
        sfml-graphics
        sfml-window
        sfml-system
)








