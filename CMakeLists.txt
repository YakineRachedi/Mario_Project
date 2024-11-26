cmake_minimum_required(VERSION 3.10)

#Nom du projet
project(Mario_Project)

#Trouver le paquet SDL2
find_package(SDL2 REQUIRED)

#Définir les fichiers sources
set(SOURCES
    test.cpp
    MARIO.cpp
    Obstacle.cpp
    Screen.cpp
)

#Définir les fichiers d'en-tête
set(HEADERS
    MARIO.hpp
    Obstacle.hpp
    Screen.hpp
)

#Créer l'exécutable (nom de l'exécutable est 'test')
add_executable(test ${SOURCES} ${HEADERS})

#Lier SDL2
target_include_directories(test PRIVATE ${SDL2_INCLUDE_DIRS})
target_link_libraries(test PRIVATE ${SDL2_LIBRARIES})