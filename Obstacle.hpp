#ifndef OBSTACLE_CLASS
#define OBSTACLE_CLASS
#include "MARIO.hpp"

class Obstacle{
    protected:
        // position en x et y, largeur et hauteur de l'obstacle
        double x, y, h, l;
        friend class Screen; // Permet à Screen d'accéder aux membres privés de Mario

    public:
        Obstacle(double _x, double _y, double _h, double _l) : x(_x), y(_y), h(_h), l(_l) {}

        // getters
        double get_position_x() const {return this->x;}
        double get_position_y() const {return this->y;}
        double get_hauteur() const {return this->h;}
        double get_largeur() const {return this->l;}
        void set_position_x(double new_x) {if (new_x >= 0) { x = new_x;}}
};

#endif