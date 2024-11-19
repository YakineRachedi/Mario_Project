#include <iostream>
#include "MARIO.hpp"
#include "Screen.hpp"
using namespace std;

int main() {
    // Instanciation de l'écran
    Screen screen;

    // Initialisation de l'écran
    if (!screen.init()) {
        cout << "Initialization error" << endl;
        return 1; // Sortie en cas d'échec
    }

    // Création d'un Mario avec des positions initiales
    Mario johnlouis(100, 200, 1, 0);

    // Boucle de jeu
    while (true) {
        if (!screen.processEvents(johnlouis)) {
            break;
        }

        screen.clear(); // Effacer l'écran
        screen.drawMario(johnlouis); // Dessiner Mario
        SDL_RenderPresent(screen.getRenderer()); // Mettre à jour l'affichage
    }

    // Fermer l'écran correctement
    screen.close();

    return 0;
}

