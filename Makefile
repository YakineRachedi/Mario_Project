# Variables de compilation
PROGS = test
CXXFLAGS = -std=c++11
SDL2_TTF_INCLUDE = /opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2
SDL2_TTF_LIB = /opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib
PKG_FLAGS = $(shell pkg-config --cflags --libs sdl2)

# Fichiers sources
SRC = test.cpp Screen.o MARIO.o Ennemi.o
OBJ = Screen.o MARIO.o Ennemi.o

# Règle par défaut
all: $(PROGS)

# Compilation de l'exécutable
test: $(OBJ) test.cpp
	@echo "Compiling executable..."
	g++ -o $@ $^ $(CXXFLAGS) $(PKG_FLAGS) \
		-I$(SDL2_TTF_INCLUDE) \
		-L$(SDL2_TTF_LIB) \
		-lSDL2_ttf

# Compilation des fichiers objets
Screen.o: Screen.cpp Screen.hpp
	g++ -c $< -o $@ $(CXXFLAGS) $(PKG_FLAGS) -I$(SDL2_TTF_INCLUDE)

MARIO.o: MARIO.cpp MARIO.hpp
	g++ -c $< -o $@ $(CXXFLAGS) $(PKG_FLAGS) -I$(SDL2_TTF_INCLUDE)

Ennemi.o: Ennemi.cpp Ennemi.hpp Obstacle.hpp
	g++ -c $< -o $@ $(CXXFLAGS) $(PKG_FLAGS) -I$(SDL2_TTF_INCLUDE)

# Nettoyage
clean:
	rm -f $(PROGS) $(OBJ)
