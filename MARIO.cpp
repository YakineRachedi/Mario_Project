#include "MARIO.hpp"
#include <assert.h>

using namespace std;

Mario::Mario(double _x, double _y, double _Vx, double _Vy): mario_x(_x), mario_y(_y), Vx(_Vx), Vy(_Vy) {
            // on initialise les param a 0 car Mario est au début de la map
            // Les vitesses dans les assetes pour s'assurer que l'utilisateur ne fait pas n'importe quoi, 
            // soit il avance, soit il recule, soit il reste dans sa place (a vitesse constante)
            assert((_Vx == -1 || _Vx == 0 || _Vx == 1) &&
                (_Vy == -1 || _Vy == 0 || _Vy == 1));
        }


void Mario::avancer(double vit_x, double vit_y, double delta_t){
            assert((vit_x == -1 || vit_x == 0 || vit_x == 1) &&
                (vit_y == -1 || vit_y == 0 || vit_y == 1));

            // Mise à jour des vitesses
            Vx = vit_x;
            Vy = vit_y;

            // Mise à jour des positions (selon l'équation du mouvement pour une vitesse constante)
            mario_x += Vx * delta_t;
            mario_y += Vy * delta_t;
        }

void Mario::render(SDL_Renderer* renderer) const {
    // static_cast<int> permet de transformer les doubles en int
    SDL_Rect rect = {static_cast<int>(mario_x), static_cast<int>(mario_y),
                     static_cast<int>(L), static_cast<int>(H)};
    SDL_SetRenderDrawColor(renderer, 255, 0, 0, 255); // Rouge
    SDL_RenderFillRect(renderer, &rect);
}
