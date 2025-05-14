#include "event.h"
#include "charactere.h"
#include <SDL2/SDL.h>

#define VITESSE_DEPLACEMENT 1
#define VITESSE_SAUT 1
#define DUREE_SAUT 200
#define SOL_Y 300

// Gère les touches pressées pour déplacer Mario
void gestionEvenement(SDL_Event *event, Personnage *mario) {
    const Uint8 *keystates = SDL_GetKeyboardState(NULL);

    // Déplacement à droite
    if (keystates[SDL_SCANCODE_RIGHT]) {
        mario->position.x += VITESSE_DEPLACEMENT;
        mario->direction = 1; // vers la droite
        mario->dernieredirection = 1;
    }
    // Déplacement à gauche
    else if (keystates[SDL_SCANCODE_LEFT]) {
        mario->position.x -= VITESSE_DEPLACEMENT;
        mario->direction = 2; // vers la gauche
        mario->dernieredirection = 2;
    }
    // Aucun déplacement horizontal
    else {
        mario->direction = 0;
    }

    // Saut (touche UP)
    if (keystates[SDL_SCANCODE_UP] && mario->jump == 0 && mario->position.y >= SOL_Y) {
        mario->jump = 1;
        mario->jumptime = DUREE_SAUT;
    }

    // Logique de saut
    if (mario->jump) {
        if (mario->jumptime > 0) {
            mario->position.y -= VITESSE_SAUT; // monte
            mario->jumptime--;
        } else {
            mario->jump = 0; // saut terminé
        }
    }
    // Gravité : retombe si pas au sol
    else if (mario->position.y < SOL_Y) {
        mario->position.y += VITESSE_SAUT;
        if (mario->position.y > SOL_Y)
            mario->position.y = SOL_Y;
    }
}
