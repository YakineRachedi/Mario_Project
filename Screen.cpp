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
    SDL_SetRenderDrawColor(m_renderer, 0, 0, 0, 255);
    SDL_RenderClear(m_renderer);
}

void Screen::close() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Screen::processEvents(Mario &mario) {
    SDL_Event event;

    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }
        if (event.type == SDL_KEYDOWN) { // Événement clavier
            switch (event.key.keysym.sym) {
                case SDLK_UP: // Flèche haut
                    mario.avancer(0, -1, 10); // Avance vers le haut
                    break;
                case SDLK_DOWN: // Flèche bas
                    mario.avancer(0, 1, 10); // Avance vers le bas
                    break;
                case SDLK_LEFT: // Flèche gauche
                    mario.avancer(-1, 0, 10); // Avance vers la gauche
                    break;
                case SDLK_RIGHT: // Flèche droite
                    mario.avancer(1, 0, 10); // Avance vers la droite
                    break;
            }
        }
    }
    return true;
}

void Screen::drawMario(const Mario &mario) {
    mario.render(m_renderer);
}