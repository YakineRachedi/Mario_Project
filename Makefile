# Variables de compilation
PROGS = test
CXXFLAGS = -std=c++11
SDL2_TTF_INCLUDE = /opt/homebrew/Cellar/sdl2_ttf/2.22.0/include/SDL2
SDL2_TTF_LIB = /opt/homebrew/Cellar/sdl2_ttf/2.22.0/lib

# Fichiers sources
SRC = test.cpp Screen.o MARIO.o
OBJ = Screen.o MARIO.o Enemi.o

# Règle par défaut
all: $(PROGS)

# Compilation de l'exécutable
test: $(SRC)
	@echo "Compiling file..."
	g++ -o $@ $^ $(CXXFLAGS) \
		$(shell pkg-config --cflags --libs sdl2) \
		-I$(SDL2_TTF_INCLUDE) \
		-L$(SDL2_TTF_LIB) \
		-lSDL2_ttf

# Compilation des fichiers objets
Screen.o: Screen.cpp
	g++ -c $< -o $@ $(CXXFLAGS) \
		$(shell pkg-config --cflags sdl2) \
		-I$(SDL2_TTF_INCLUDE)

MARIO.o: MARIO.cpp
	g++ -c $< -o $@ $(CXXFLAGS) \
		$(shell pkg-config --cflags sdl2)

Enemi.o: Enemi.hpp
	g++ -c $< -o $@ $(CXXFLAGS) \
		$(shell pkg-config --cflags sdl2)
# Nettoyage
clean:
	rm -f $(PROGS) $(OBJ)
