cmake_minimum_required(VERSION 3.10)

# ces deux lignes pour le mac
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

project(Mario_Project)

# Trouver le paquet SDL2
find_package(SDL2 REQUIRED)

# Spécifie manuellement le chemin d'inclusion pour SDL2_ttf
set(SDL2_TTF_INCLUDE_DIRS "/opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2")  # Chemin d'inclusion de SDL2_ttf

# Trouver SDL2_ttf avec les chemins manuels
find_library(SDL2_TTF_LIBRARY NAMES SDL2_ttf PATHS /opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib)

message(STATUS "SDL2 include dirs: ${SDL2_INCLUDE_DIRS}")
message(STATUS "SDL2_ttf include dirs: ${SDL2_TTF_INCLUDE_DIRS}")

set(SOURCES
    test.cpp
    MARIO.cpp
    Screen.cpp
)

set(HEADERS
    MARIO.hpp
    Obstacle.hpp
    Screen.hpp
    Enemi.hpp
)

add_executable(test ${SOURCES} ${HEADERS})

# Lier SDL2 et SDL2_ttf
target_include_directories(test PRIVATE ${SDL2_INCLUDE_DIRS} ${SDL2_TTF_INCLUDE_DIRS})
target_link_libraries(test PRIVATE ${SDL2_LIBRARIES} ${SDL2_TTF_LIBRARY})

