#ifndef SCREEN_CLASS
#define SCREEN_CLASS


#include <iostream>
#include <SDL2/SDL.h>
#include <SDL_ttf.h>
#include <assert.h>
#include "MARIO.hpp"
#include "Obstacle.hpp"
#include "Ennemi.hpp"
#include <stdexcept>  // Pour std::exception

// Dimensions de l'écran
#define SCREEN_WIDTH 1080
#define SCREEN_HEIGHT 960


class Screen{

    private :
        SDL_Window *m_window;
        friend class GameManager;
    protected :
        SDL_Renderer *m_renderer;
    public :
        Screen();
        bool init();
        void close();
        void clear();
        bool processEvents(Mario & mario, const std::vector<Obstacle> & obstacles,std::vector<Ennemi> & ennemy); //faire tourner le jeux
        
        // Méthodes pour l'affichage
        void drawMario(const Mario & mario) const;  // Dessiner Mario à sa position actuelle
        void drawBackground() const ;               // Dessinier le ciel et le sol
        void update();                       // Mettre à jour l'écran (actualiser l'affichage)
        void drawObstacle(const Obstacle & terrainObstacle) const ; // Dessinier les obstacles
        void drawEnnemi(const Ennemi & terrainEnnemi) const;
        void showGameOverMessage() const;

        SDL_bool IsCollidingObstacle(const Mario & mario, const Obstacle & object) const; // pour tester l'intersection avec mario
        bool checkCollisionInDirectionObstacle(const Mario & mario, const std::vector<Obstacle> & obstacles, int dx, int dy) const;

        bool IsCollidingEnnemi(const Mario & mario, const Ennemi & object) const;
        bool IsCollidingEnnemiObstacle(const Obstacle & object, const Ennemi & Ennemy) const;


};


// Exception personnalisée pour l'état Game Over
class GameOverException : public std::exception {
public:
    const char* what() const noexcept override {
        return "Game Over: Collision avec un ennemi !";
    }
};
#endif