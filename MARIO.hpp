#ifndef MARIO_CLASS
#define MARIO_CLASS

#include <assert.h>
#include <vector>
#include <SDL2/SDL.h>

class Screen;

//#define SCREEN_WIDTH 1080
//#define SCREEN_HEIGHT 960
//#define GROUND SCREEN_HEIGHT / 2
#define DT 0.1

class Mario{
    private :
        double mario_x, mario_y;              // position selon l'axe x et y
        double Vx, Vy;                        // vitesse selon x et y
        static constexpr double L = 40.0;    // Largeur
        static constexpr double H = 50.0;    // Hauteur
        bool isJumping;          // Indique si Mario est en train de sauter

        friend class Screen;                // Permet à Screen d'accéder aux membres privés de Mario

    public :
        
        Mario(double _x = 0, double _y = 0, double _Vx = 0, double _Vy = 0);
        double get_position_x() const {return this->mario_x;}
        double get_position_y() const {return this->mario_y;}
        double get_vitesse_x() const {return this->Vx;}
        double get_vitesse_y() const {return this->Vy;}
        double get_hauteur() const {return this->H;}
        double get_largeur() const {return this->L;}
        void avancer(double vit_x, double vit_y, double delta_t);
        void saute(double delta_t);
        void update(double delta_t); // Mise à jour générale


};

#endif