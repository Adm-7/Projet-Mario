#include <stdlib.h>
#include <stdio.h>

#include "charactere.h"


/*void chargerMario(Personnage* mario, SDL_Renderer *renderer) {
    mario->image = IMG_LoadTexture(renderer, "mario.png");
    if (!mario->image) {
    printf("Erreur de chargement de Mario : %s\n", SDL_GetError());
    exit(1);
    }
}*/

void freePersonnage(Personnage* mario, Personnage **goomba, int nbGoomba) {
    
}