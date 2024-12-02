#ifndef OBSTACLE_CLASS
#define OBSTACLE_CLASS
#include "MARIO.hpp"


class Obstacle{
    protected:
        // position en x et y, largeur et hauteur de l'obstacle
        double x, y, h, l;
        friend class Screen; // Permet à Screen d'accéder aux membres privés de Mario

    public:
        // méthode contacte à faire soit ici soit dans la classe Mario !
        Obstacle(double _x, double _y, double _h, double _l) : x(_x), y(_y), h(_h), l(_l) {}

        // getters
        double get_position_x() const {return this->x;}
        double get_position_y() const {return this->y;}
        double get_hauteur() const {return this->h;}
        double get_largeur() const {return this->l;} 
};

#endif