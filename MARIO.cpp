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
            Vx = vit_x;
            Vy = vit_y;

            // Mise à jour des positions (selon l'équation du mouvement pour une vitesse constante)
            mario_x += Vx * delta_t;
            mario_y += Vy * delta_t;
        }

/*
void Mario::saute(double saute_x, double saute_y, double delta_t){
    assert((saute_x == -1 || saute_x == 0 || saute_x == 1) &&
        (saute_y == 0 || saute_y == 1));
    // vitesses initiales
    Vx = saute_x;
    Vy = saute_y;

    const double gravity = -9.80665; // Constante gravitationnelle (orientée vers le bas pourcela y a un -)
    
    // Met à jour la position pendant le saut
    mario_y += Vy * delta_t + 0.5 * gravity * delta_t * delta_t; // position y avec gravité 
                                                // (ici l'accélération = gravité pas sur raisons physiques xD !)
    mario_x += Vx * delta_t;  // position x sans gravité (selon l'axe ox)

    // Mise à jour de la vitesse en y (Vy décroît pour simuler la chute)
    Vy += gravity * delta_t; // de meme accélariton = gravité

    // Gestion du sol (si Mario descend en dessous de 0, on le ramène au sol)
    if (mario_y < 0) {
        mario_y = 0;
        Vy = 0; // Arrête le mouvement vertical si Mario touche le sol
    }
}
*/

void Mario::saute(double delta_t) {
    if (!isJumping) {
        mario_y -= 10;
        Vy = -15; // Vitesse initiale du saut
        isJumping = true;
    }
}

void Mario::update(double delta_t) {
    const double gravity = 9.8;

    // Appliquer la gravité si Mario est en saut
    if (isJumping) {
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