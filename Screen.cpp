#include "Screen.hpp"
#include <iostream>
using namespace std;

Screen::Screen() {
    m_window = NULL;
    m_renderer = NULL;
}


bool Screen::init() {
    if (SDL_Init(SDL_INIT_VIDEO) < 0) {
        cout << "Error SDL initialization ..." << endl;
        return false;
    }

    m_window = SDL_CreateWindow("Titre de la fenetre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == NULL) {
        cout << "Pb with window" << endl;
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == NULL) {
        cout << "Erreur de creation de renderer" << endl;
        SDL_DestroyWindow(m_window);
        SDL_Quit();
        return false;
    }

    return true;
}

void Screen::clear() {
    //SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); ici background noir
    //drawBackground();
    //SDL_SetRenderDrawColor(m_renderer, 135, 206, 235, 255);  // Bleu ciel pour le fond initial
    SDL_RenderClear(m_renderer);
}

void Screen::close() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Screen::processEvents(Mario & mario, const std::vector<Obstacle> & obstacles) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }

        if (event.type == SDL_KEYDOWN) {
            
            // Contrôler Mario avec les touches
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    if (!checkCollisionInDirection(mario, obstacles, -1, 0)) {
                        mario.avancer(-1, 0, DT); // Avance vers la gauche
                    }                    
                    break;
                case SDLK_RIGHT:
                    if (!checkCollisionInDirection(mario, obstacles, 1, 0)) {
                        mario.avancer(1, 0, DT); // Avance vers la droite
                    }
                    break;
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_SPACE) {
                mario.saute(DT); // Initie le saut
            }
        }
            // Vérification de la collision avec chaque obstacle
        for (const Obstacle &obstacle : obstacles) {
            if (IsColliding(mario, obstacle)) {
                std::cout << "Intersection de Mario avec l'obstacle !!!" << std::endl;
                // on peut ajouter des actions ici
                // Mario pourrait être repositionné ou son mouvement pourrait être stoppé.
                // Bloquer Mario dans la direction du saut si collision avec le sol
                if (mario.mario_y + mario.H <= obstacle.y + obstacle.h) {
                    mario.mario_y = obstacle.y - mario.H;  // Empêcher Mario de passer à travers le sol
                }
            }
        }
    }
    return true;
}

void Screen::drawMario(const Mario & mario) {
    SDL_Rect rect = {static_cast<int>(mario.mario_x), static_cast<int>(mario.mario_y), // mario à sa position actuelle
                     static_cast<int>(mario.H),static_cast<int>(mario.L)};

    SDL_SetRenderDrawColor(m_renderer, 255, 0, 0, 255); // Mario en rouge
    SDL_RenderFillRect(m_renderer, &rect);
    
}

void Screen::update() {
    SDL_RenderPresent(m_renderer); // Actualiser l'écran et mettre à jours
}

void Screen::drawBackground() {
    // Dessiner le ciel
    SDL_SetRenderDrawColor(m_renderer, 135, 206, 235, 255); // Bleu ciel
    SDL_Rect skyRect = {0, 0, SCREEN_WIDTH, SCREEN_HEIGHT / 2}; // La moitié supérieure de l'écran
    SDL_RenderFillRect(m_renderer, &skyRect);

    // Dessiner le sol
    SDL_SetRenderDrawColor(m_renderer, 34, 139, 34, 255); // Vert pour le sol
    SDL_Rect groundRect = {0, SCREEN_HEIGHT / 2, SCREEN_WIDTH, SCREEN_HEIGHT / 2}; // La moitié inférieure
    SDL_RenderFillRect(m_renderer, &groundRect);
}


void Screen::drawObstacle(const Obstacle & terrainObstacle){
    SDL_Rect rect = {static_cast<int>(terrainObstacle.x), static_cast<int>(terrainObstacle.y),
             static_cast<int>(terrainObstacle.h), static_cast<int>(terrainObstacle.l)};
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255); // Noir
    SDL_RenderFillRect(m_renderer, &rect);
}

SDL_bool Screen::IsColliding(const Mario &mario, const Obstacle &object) {
    // je récupère la position du rectangle qui représente Mario    
    SDL_Rect marioRect = {
        static_cast<int>(mario.mario_x), static_cast<int>(mario.mario_y),
        static_cast<int>(mario.L), static_cast<int>(mario.H)
    };
    // je récupère la position du rectangle qui représente l'obstacle
    SDL_Rect objectRect = {
        static_cast<int>(object.x), static_cast<int>(object.y),
        static_cast<int>(object.l), static_cast<int>(object.h)
    };

    return SDL_HasIntersection(&marioRect, &objectRect); // je test l'intersection avec la fonction prédéfinie
}

/*
bool Screen::checkCollision(const Mario & mario, const std::vector<Obstacle> & obstacles) {
    for (const Obstacle &obstacle : obstacles) {
        if (IsColliding(mario, obstacle)) {
            return true;  // Collision détectée
        }
    }
    return false;  // Pas de collision
}
*/

bool Screen::checkCollisionInDirection(const Mario & mario, const std::vector<Obstacle> & obstacles, int dx, int dy) {
    
    // crée un "mouvement futur" pour Mario (en tenant compte de la direction)
    float future_x = mario.mario_x + dx;
    float future_y = mario.mario_y + dy;

    // crée un rectangle qui représente Mario dans sa position future
    SDL_Rect marioFutureRect = {
        static_cast<int>(future_x), static_cast<int>(future_y),
        static_cast<int>(mario.L), static_cast<int>(mario.H)
    };


    for (const Obstacle &obstacle : obstacles) { // boucle pour vérifier détecter les collisiobs
        SDL_Rect objectRect = {
            static_cast<int>(obstacle.x), static_cast<int>(obstacle.y),
            static_cast<int>(obstacle.l), static_cast<int>(obstacle.h)
        };
        
        if (SDL_HasIntersection(&marioFutureRect, &objectRect)) {
            return true;  // collision détectée bloque le mouvement -><- -><- -><-
        }
    }

    return false; // Aucune collision -> -> ->  Mario peut se déplacer -> -> ->
}
