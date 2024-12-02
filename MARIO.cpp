#include "MARIO.hpp"
#include <assert.h>

using namespace std;

Mario::Mario(double _x, double _y, double _Vx, double _Vy): mario_x(_x), mario_y(_y), Vx(_Vx), Vy(_Vy), isJumping(false) {
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
            if (isJumping){
                 Vx = 25*vit_x; // Modifier la vitesse Vx car sinon mario saute trop loin
            }
            else{
                Vx = 100*vit_x; // Modifier la vitesse car sinon mario est trop lent
            }
            
            Vy = 100*vit_y;

            // Mise à jour des positions (selon l'équation du mouvement pour une vitesse constante)
            mario_x += Vx * delta_t;
            mario_y += Vy * delta_t;
        }

void Mario::saute(double delta_t) {
    if (!isJumping) {
        mario_y -= 30;
        Vy = -15; // Vitesse initiale du saut
        Vx /= 4; 

        isJumping = true;
    }
}

void Mario::update(double delta_t) {
    const double gravity = 9.8;

    // Appliquer la gravité si Mario est en saut
    if (isJumping || mario_y + H < 440) {
        
        mario_x += Vx * delta_t;
        mario_y += Vy * delta_t;
        Vy += gravity * delta_t;
        // Vérifier si Mario touche le sol
        if (mario_y >= 440) {
            mario_y = 440;
            Vy = 0;
            isJumping = false;
        }
     
    }

    // Limiter les positions (par exemple, pour rester dans l'écran)
    if (mario_x < 0) mario_x = 0;
    if (mario_x > 800 - L) mario_x = 800 - L; // Limite horizontale
}
