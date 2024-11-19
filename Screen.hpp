#ifndef SCREEN_CLASS
#define SCREEN_CLASS


#include <iostream>
#include <SDL2/SDL.h>
#include <assert.h>
#include "MARIO.hpp"

class Screen{

    private :
        SDL_Window *m_window;
    protected :
        SDL_Renderer *m_renderer;
    public :
        const static int SCREEN_WIDTH = 1080;
        const static int SCREEN_HEIGHT = 960;
        Screen();
        bool init();
        void close();
        void clear();
        bool processEvents(Mario & mario);
        void test();
        void drawMario(const Mario & mario); // Méthode pour dessiner Mario
        SDL_Renderer* getRenderer() const { return m_renderer; }


};

#endif