 #include <SDL2/SDL.h>
#include "charactere.h"

// Fonction pour charger l'image de Mario
void chargerMario(Personnage *mario, SDL_Renderer *renderer){
    mario->image= malloc(6 * sizeof(SDL_Texture*));
    if (mario->image == NULL)
    {
        perror("Erreur d'allocation mémoire pour les images de Mario\n");
        exit(1);
    }
    mario->image[0] = loadImage("img/Mario1.png", renderer);
    mario->image[1] = loadImage("img/Mario2.png", renderer);
    mario->image[2] = loadImage("img/Mario3.png", renderer);
    mario->image[3] = loadImage("img/Mario4.png", renderer);
    mario->image[4] = loadImage("img/Mario5.png", renderer);
    mario->image[5] = loadImage("img/Mario6.png", renderer);
        
    


    // Initialisation de la position de Mario
    mario->position.x = 100;
    mario->position.y = 300;
    mario->position.w = WIDTH_MARIO;
    mario->position.h = HEIGHT_MARIO;

    mario->jump = 0;
    mario->jumptime = 0;
    mario->direction = 1;
    mario->dernieredirection = 1;
    mario->win = 0;
}


// Fonction pour afficher Mario
// Fonction pour afficher Mario selon sa direction
void afficherPerso(Personnage *mario, int xscroll, int yscroll, SDL_Renderer *renderer)
{
    SDL_Texture *textureActuelle = NULL;

    // Choisir l'image selon la direction ou l'état
    if (mario->jump == 1) {
        textureActuelle = mario->image[2];// Image de saut
    }else if(mario->direction == 2){
        textureActuelle = mario->image[5];
    }
    else if (mario->direction == 1) {
        textureActuelle = mario->image[1]; // Marche droite
    }
    else if (mario->direction == 2) {
        textureActuelle = mario->image[4]; // Marche gauche
    }
    else if (mario->dernieredirection == 1) {
        textureActuelle = mario->image[0]; // Immobile vers droite
    }
    else {
        textureActuelle = mario->image[3]; // Immobile vers gauche
    }

    SDL_RenderCopy(renderer, textureActuelle, NULL, &mario->position);
}


// Fonction pour libérer la mémoire
void freePersonnage(Personnage *mario, Personnage **goomba, int nbGoomba)
{
    if (mario->image && *(mario->image)) {
        SDL_DestroyTexture(*(mario->image));
        *(mario->image) = NULL;
    }
    
    for (int i = 0; i < nbGoomba; i++)
    {
        if (goomba[i] && goomba[i]->image)
        {
            SDL_DestroyTexture(*(goomba[i]->image));
        }
        free(goomba[i]);
    }
    free(goomba);
}
