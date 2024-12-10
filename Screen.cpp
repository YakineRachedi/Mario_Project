#include "Screen.hpp"
#include <iostream>
#include <thread>  // Nécessaire pour std::this_thread::sleep_for
#include <chrono>  // Pour chrono::seconds

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
    if (TTF_Init() == -1) {
        cout << "SDL_ttf could not initialize! TTF_Error: " << TTF_GetError() << endl;
        SDL_Quit();
        return false;
    }
    m_window = SDL_CreateWindow("Titre de la fenetre", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT, SDL_WINDOW_SHOWN);
    if (m_window == NULL) {
        cout << "Pb with window" << endl;
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
    if (m_renderer == NULL) {
        cout << "Erreur de creation de renderer" << endl;
        SDL_DestroyWindow(m_window);
        TTF_Quit();
        SDL_Quit();
        return false;
    }

    return true;
}

void Screen::clear() {
    SDL_RenderClear(m_renderer);
}

void Screen::close() {
    SDL_DestroyRenderer(m_renderer);
    SDL_DestroyWindow(m_window);
    SDL_Quit();
}

bool Screen::processEvents(Mario & mario, const std::vector<Obstacle> & obstacles, const std::vector<Enemi> & ennemy) {
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        if (event.type == SDL_QUIT) {
            return false;
        }

        if (event.type == SDL_KEYDOWN) { // SDL_KEYDOWN est utilisé pour détecter les touches pressées
            // Contrôler Mario avec les touches
            switch (event.key.keysym.sym) {
                case SDLK_LEFT:
                    if (!checkCollisionInDirectionObstacle(mario, obstacles, -1, 0)) {
                        mario.avancer(-1, 0, DT); // Avance vers la gauche
                    }                    
                    break;
                case SDLK_RIGHT:
                    if (!checkCollisionInDirectionObstacle(mario, obstacles, 1, 0)) {
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
            if (IsCollidingObstacle(mario, obstacle)) {
                std::cout << "Intersection de Mario avec l'obstacle !!!" << std::endl;
                // on peut ajouter des actions ici
                // Mario pourrait être repositionné ou son mouvement pourrait être stoppé.
                // Bloquer Mario dans la direction du saut si collision avec le sol
                if (mario.mario_y + mario.H <= obstacle.y + 10) { 
                    // Mario est juste au-dessus de l'obstacle
                    mario.mario_y = obstacle.y - mario.H;  // positionner Mario au sommet de l'obstacle
                    mario.Vy = 0;  // annuler sa vitesse verticale
                    mario.isJumping = false;  // Mario n'est plus en train de sauter
                }
            }
        }
        try {
            // Vérifier les collisions avec les ennemis
            for (const Enemi &object : ennemy) {
                if (IsCollidingEnemi(mario, object)) {
                    // Lancer l'exception GameOverException
                    throw GameOverException();
                }
            }
        } 

        catch (const GameOverException& e) {
            // Gérer l'exception GameOver (afficher message et attendre 5 secondes)
            showGameOverMessage(); // Afficher le message Game Over
            cout << "GAME OVER \n";
            cout << "GAME OVER \n";
            cout << "GAME OVER \n";
            std::this_thread::sleep_for(std::chrono::seconds(5)); // Attendre 5 secondes avant de quitter
            return false; // Retourner false pour signaler que le jeu est terminé
        }
    }

    // Si aucune collision, mise à jour de l'écran
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

void Screen::drawEnemi(const Enemi & terrainEnnemi){
    SDL_Rect rect = {static_cast<int>(terrainEnnemi.x), static_cast<int>(terrainEnnemi.y),
             static_cast<int>(terrainEnnemi.h), static_cast<int>(terrainEnnemi.l)};
    SDL_SetRenderDrawColor(m_renderer, 0, 255, 0, 255); // Vert
    SDL_RenderFillRect(m_renderer, &rect);
}

SDL_bool Screen::IsCollidingObstacle(const Mario &mario, const Obstacle &object) {
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

bool Screen::checkCollisionInDirectionObstacle(const Mario & mario, const std::vector<Obstacle> & obstacles, int dx, int dy) {
    
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


bool Screen::IsCollidingEnemi(const Mario & mario, const Enemi & object) {
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


void Screen::showGameOverMessage() {
    // Afficher un texte "GAME OVER" au centre de l'écran
    SDL_Color textColor = {255, 0, 0}; // Rouge
    TTF_Font *font = TTF_OpenFont("/System/Library/Fonts/Supplemental/Arial.ttf", 48);
    if (!font) {
        std::cerr << "Erreur de chargement de la police : " << TTF_GetError() << std::endl;
        return;
    }

    SDL_Surface *textSurface = TTF_RenderText_Solid(font, "GAME OVER", textColor);
    SDL_Texture *textTexture = SDL_CreateTextureFromSurface(m_renderer, textSurface);
    if (!textTexture) {
        std::cerr << "Erreur de création de la texture : " << SDL_GetError() << std::endl;
        SDL_FreeSurface(textSurface);
        TTF_CloseFont(font);
        return;
    }
    SDL_Rect textRect = {200, 200, 300, 100}; // Position et taille du texte
    SDL_RenderCopy(m_renderer, textTexture, NULL, &textRect);
    SDL_DestroyTexture(textTexture);

    SDL_RenderPresent(m_renderer); // Mettre à jour l'écran
}
