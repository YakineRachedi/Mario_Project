#include <iostream>
#include "Screen.hpp"
#include "MARIO.hpp"
#include <vector>


using namespace std;

int main() {
    Screen screen;
    const int GROUND = 440;
    Ennemi ennemi(650, 450, 50, 30);
    vector<Obstacle> obstacles = {
    Obstacle(200, 450, 70, 40),
    Obstacle(400, 450, 50, 40),  
    //Obstacle(600, 450, 50, 30)
};
    if (!screen.init()) {
        cout << "Erreur lors de l'initialisation de la fenêtre !" << endl;
        return -1;
    }

    Mario mario(0,GROUND);
    bool running = true;
    while (running) {
        screen.clear();  // Efface l'écran au début de chaque frame
        screen.drawBackground();
        screen.drawEnnemi(ennemi);
        for (const auto& obstacle : obstacles) {
            screen.drawObstacle(obstacle);  // Dessiner chaque obstacle
        } 

        mario.update(DT); // Met à jour Mario avec un delta_t (par exemple 16 ms)
        screen.drawMario(mario);  // Dessiner Mario
        running = screen.processEvents(mario, obstacles);  // Traiter les événements utilisateur

        screen.update();  // Mettre à jour l'affichage
    }
    screen.close();
    return 0;
}
