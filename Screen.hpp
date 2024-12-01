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
        bool processEvents(Mario & mario, const std::vector<Obstacle> & obstacles); //faire tourner le jeux
        void test();
        
        // Méthodes pour l'affichage
        void drawMario(const Mario & mario);  // Dessiner Mario à sa position actuelle
        void drawBackground();               // Dessinier le ciel et le sol
        void update();                       // Mettre à jour l'écran (actualiser l'affichage)
        void drawObstacle(const Obstacle & terrainObstacle); // Dessinier les obstacles

        SDL_bool IsColliding(const Mario & mario, const Obstacle & object); // pour tester l'intersection avec mario
        // bool checkCollision(const Mario & mario, const std::vector<Obstacle> & obstacles)
        bool checkCollisionInDirection(const Mario & mario, const std::vector<Obstacle> & obstacles, int dx, int dy);
};

#endif