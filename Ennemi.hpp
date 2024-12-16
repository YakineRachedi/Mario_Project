#ifndef ENNEMI_CLASS
#define ENNEMI_CLASS

#include "Obstacle.hpp"
#include <random>

class Ennemi : public Obstacle {
    public:
    // Constructeur qui utilise celui de Obstacle
    Ennemi(double _x, double _y, double _h, double _l) 
        : Obstacle(_x, _y, _h, _l) {}

    void moveRandomely(std::mt19937 & G);
};

#endif
