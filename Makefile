PROGS = test
CXXFLAGS = -I/usr/include/SDL2 -L/usr/lib -lSDL2

all: $(PROGS)

test: test.cpp Screen.o MARIO.o
	@echo "Compiling file..."
	g++ -o $@ $^ $(CXXFLAGS)

Screen.o: Screen.cpp
	g++ -c $< -o $@

MARIO.o: MARIO.cpp
	g++ -c $< -o $@

clean:
	rm -f $(PROGS) *.o
