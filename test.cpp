#include <iostream>
#include "Screen.hpp"
#include "MARIO.hpp"
#include <SDL2/SDL.h>  // SDL pour la gestion des événements et l'affichage
#include <vector>


using namespace std;

int main() {
    Screen screen;
    const int GROUND = 440;
    vector<Obstacle> obstacles = {
    Obstacle(200, GROUND, 50, 50),
    Obstacle(400, GROUND, 30, 30),  
    Obstacle(600, GROUND, 40, 20)
};
    if (!screen.init()) {
        cout << "Erreur lors de l'initialisation de la fenêtre !" << endl;
        return -1;
    }

//    Mario mario(100.0, GROUND, 0.0, 0.0); // defauts ici meme si je mets Vx = 0 et Vy = 0 il bouge
    Mario mario(0,GROUND);
//    Mario mario;
    bool running = true;
    while (running) {
        screen.clear();  // Efface l'écran au début de chaque frame
        screen.drawBackground();
        for (const auto& obstacle : obstacles) {
            screen.drawObstacle(obstacle);  // Dessiner chaque obstacle
        } 

        mario.update(4); // Met à jour Mario avec un delta_t (par exemple 16 ms)
        screen.drawMario(mario);  // Dessiner Mario
        cout << "boucle principale \n";
        running = screen.processEvents(mario);  // Traiter les événements utilisateur

        screen.update();  // Mettre à jour l'affichage
    }
    screen.close();
    return 0;
}
