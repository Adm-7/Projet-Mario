/*
Gère les différents évènements du jeu comme le mouvement des personnages et des ennemies, les collisions, le scroll de la map
et si le niveau est fini (win et loose). 
*/

#ifndef DEF_EVENT
#define DEF_EVENT
    
    #include "file.h"
    #include "charactere.h"
    #include "game.h"
    #include <SDL2/SDL.h>
    void gestionEvenement(SDL_Event *event, Personnage *perso);

  
#endif