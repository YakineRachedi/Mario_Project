#include <iostream>
#include "Screen.hpp"
#include "MARIO.hpp"
#include <vector>
#include <ctime>

using namespace std;

int main() {
    Screen screen;
    if (!screen.init()) {
        cout << "Failed to initialize!" << endl;
        return -1;
    }

    
    Mario mario(0, GROUND, 0, 0); // Initialiser Mario au sol

    vector<Obstacle> obstacles = {
        Obstacle(200, GROUND + 10, 40, 30),
        Obstacle(400, GROUND + 10, 40, 30)
    };

    vector<Ennemi> ennemies = {
        Ennemi(650, GROUND + 10, 30, 30)
    };
    std::mt19937 G(time(nullptr));
    bool running = true;
    while (running) {
        screen.clear();
        screen.drawBackground();
        screen.drawMario(mario);
        
        for (const auto &obs : obstacles) {
            screen.drawObstacle(obs);
        }

        for (auto &enn : ennemies) {
            enn.moveRandomely(G);
            screen.drawEnnemi(enn);
        }

        mario.update(DT);
        running = screen.processEvents(mario, obstacles, ennemies);

        screen.update();
    }

    screen.close();
    return 0;
}
