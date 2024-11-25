#ifndef SCREEN_CLASS
#define SCREEN_CLASS


#include <iostream>
#include <SDL2/SDL.h>
#include <assert.h>
#include "MARIO.hpp"
#include "Obstacle.hpp"
// Dimensions de l'écran
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 960

class Screen{

    private :
        SDL_Window *m_window;
    protected :
        SDL_Renderer *m_renderer;
    public :
        Screen();
        bool init();
        void close();
        void clear();
        bool processEvents(Mario & mario);
        void test();
        
        // Méthodes pour l'affichage
        void drawMario(const Mario & mario);  // Dessiner Mario à sa position actuelle
        void drawBackground();               // Dessinier le ciel et le sol
        void update();                       // Mettre à jour l'écran (actualiser l'affichage)
        void drawObstacle(const Obstacle & terrainObstacle);

};

#endif