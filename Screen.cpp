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

bool Screen::processEvents(Mario & mario) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }

        if (event.type == SDL_KEYDOWN) {
            
            // Contrôler Mario avec les touches
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    mario.avancer(-1, 0, DT); // Avance vers la gauche
                    break;
                case SDLK_RIGHT:
                    mario.avancer(1, 0, DT); // Avance vers la droite
                    break;
            }
        }
        if (event.type == SDL_KEYUP) {
            if (event.key.keysym.sym == SDLK_SPACE) {
                mario.saute(DT); // Initie le saut
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
