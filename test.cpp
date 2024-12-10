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

    
    Mario mario(0, GROUND, 0, 0); // Initialiser Mario au sol

    vector<Obstacle> obstacles = {
        Obstacle(200, GROUND, 40, 30),
        Obstacle(400, GROUND, 40, 30)
    };

    vector<Ennemi> ennemies = {
        Ennemi(650, GROUND - 50, 30, 50)
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
            screen.drawEnnemi(enn);
        }

        mario.update(DT);
        running = screen.processEvents(mario, obstacles, ennemies);

        screen.update();
    }

    screen.close();
    return 0;
}
