#ifndef ENNEMI_CLASS
#define ENNEMI_CLASS

#include "Obstacle.hpp"

class Ennemi : public Obstacle {
    public:
    // Constructeur qui utilise celui de Obstacle
    Ennemi(double _x, double _y, double _h, double _l) 
        : Obstacle(_x, _y, _h, _l) {}
};
#endif
