/*
Contient le coeur du programme une fois qu'on a passé le menu, va interagir avec les autres classes.
Ce fichier va appeler toutes les méthodes pour créer le personnage, la map, afficher les éléments, déplacer le personnage, ...
Mais ne contient pas les déclarations des différentes  fonctions utilisées.
*/

#ifndef DEF_GAME
#define DEF_GAME
    #include <SDL2/SDL.h>
    #include "file.h"
    #include "charactere.h"
    #include "event.h"

    int jouer(SDL_Renderer* renderer);
    void InitialiserSprites(Sprites* sprites, SDL_Renderer* renderer); // Déclaration ajoutée
   
#endif