#include <iostream>
#include "Screen.hpp"
#include "MARIO.hpp"
#include <vector>


using namespace std;

int main() {
    Screen screen;
    if (!screen.init()) {
        cout << "Failed to initialize!" << endl;
        return -1;
    }

    const int GROUND = 440; // Limite verticale du sol
    Mario mario(0, GROUND, 0, 0); // Initialiser Mario au sol

    vector<Obstacle> obstacles = {
        Obstacle(200, GROUND, 40, 30),
        Obstacle(400, GROUND, 40, 30)
    };

    vector<Enemi> ennemies = {
        Enemi(650, GROUND - 50, 30, 50)
    };

    bool running = true;
    while (running) {
        screen.clear();
        screen.drawBackground();
        screen.drawMario(mario);
        
        for (const auto &obs : obstacles) {
            screen.drawObstacle(obs);
        }

        for (const auto &enn : ennemies) {
            screen.drawEnemi(enn);
        }

        mario.update(DT);
        running = screen.processEvents(mario, obstacles, ennemies);
        //gameManager.handleState(screen);

        screen.update();
    }

    screen.close();
    return 0;
}
