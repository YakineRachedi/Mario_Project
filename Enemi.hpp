#ifndef ENEMI_CLASS
#define ENEMI_CLASS

#include "Obstacle.hpp"

class Enemi : public Obstacle {
    public:
    // Constructeur qui utilise celui de Obstacle
    Enemi(double _x, double _y, double _h, double _l) 
        : Obstacle(_x, _y, _h, _l) {}

    
};
#endif
