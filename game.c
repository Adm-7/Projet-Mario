#include "game.h"
#include "event.h" 

void AfficherMapAvecScrolling(Map* map, Sprites* sprites, SDL_Renderer* renderer, int xscroll) {
    int startCol = xscroll / Size_Sprite; // Colonne de départ
    int endCol = startCol + (LARGEUR_FENETRE / Size_Sprite) + 1; // Colonne de fin (+1 pour éviter les artefacts)

    if (endCol > map->width) {
        endCol = map->width; // Empêcher de dépasser la largeur de la map
    }

    for (int i = 0; i < map->height; i++) {
        for (int j = startCol; j < endCol; j++) {
            int spriteIndex = map->LoadedMap[i][j];
            if (spriteIndex >= 0 && spriteIndex < NbSprites) {
                SDL_Rect dest = { (j - startCol) * Size_Sprite, i * Size_Sprite, Size_Sprite, Size_Sprite };
                SDL_RenderCopy(renderer, sprites[spriteIndex].sprite, NULL, &dest);
            }
        }
    }
}

int jouer(SDL_Renderer* renderer) {
      
    // charger image et personnage.
    Personnage *mario = malloc(sizeof(Personnage));
    chargerMario(mario, renderer);

    // Charger la map niveau1
    Map map = {0};
    LireLevel1(&map);

    // Initialisation des sprites
    Sprites sprites[NbSprites];
    InitialiserSprites(sprites, renderer);
    

     
    // Initialisation des variables
    int continuer = 1; // À utiliser pour savoir si on continue la boucle du jeu ou si on arrête
    SDL_Event event;  // Déclaration de l'événement
    int xscroll = 0; // Position de défilement horizontal

    // Configuration de la couleur de fond (blanc)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
   
    while(continuer) { // Coeur du jeu ici, les actions seront répétées pour faire le déplacement des différentes images, etc.
        SDL_RenderClear(renderer);
        // Afficher la map avec scrolling
        AfficherMapAvecScrolling(&map, sprites, renderer, xscroll);

        SDL_RenderPresent(renderer);
        // Gérer les différentes actions
        while (SDL_PollEvent(&event)) {  // Boucle qui gère les événements
            switch (event.type) {
                case SDL_QUIT:  // Si l'utilisateur ferme la fenêtre
                    continuer = 0;
                    break;

                case SDL_KEYDOWN:  // Si une touche est pressée
                    switch(event.key.keysym.sym) {
                        case SDLK_ESCAPE:  // Si la touche échappe est pressée
                            continuer = 0;
                            break;

                        case SDLK_1:  // Si la touche '1' est pressée
                            // Ici tu peux ajouter le code pour afficher la map Mario
                            // Exemple : afficherMap(renderer, map, sprites);
                            break;
                        case SDLK_RIGHT: // Défilement vers la droite
                            xscroll += 10;
                            if (xscroll > (map.width * Size_Sprite - LARGEUR_FENETRE)) {
                                xscroll = map.width * Size_Sprite - LARGEUR_FENETRE;
                            }
                            break;

                        case SDLK_LEFT: // Défilement vers la gauche
                            xscroll -= 10;
                            if (xscroll < 0) {
                                xscroll = 0;
                            }
                            break;

                default:
                    break;
                }
                break;

            default:
                break;
            }
        }
        gestionEvenement(&event, mario);
        afficherPerso(mario, 1, 1, renderer);
        // À ce stade, tu devrais dessiner et mettre à jour les objets du jeu
        // Afficher la scène et mettre à jour l'écran
        SDL_RenderPresent(renderer);

    }

    // Libération des ressources
    freePersonnage(mario, NULL, 0);
    free(mario);
    LibererMap(&map, sprites);
    return 0;
}
