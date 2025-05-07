#include "game.h"
#include "file.h"
#include "charactere.h"
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
    // Charger la map niveau1
    Map map = {0};
    LireLevel1(&map);

    // Initialisation des sprites
    Sprites sprites[NbSprites];
    InitialiserSprites(sprites, renderer);

    // Initialisation des variables
    int continuer = 1;
    SDL_Event event;
    int xscroll = 0; // Position de défilement horizontal

    // Configuration de la couleur de fond (blanc)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);

    while (continuer) {
        SDL_RenderClear(renderer);

        // Afficher la map avec scrolling
        AfficherMapAvecScrolling(&map, sprites, renderer, xscroll);

        SDL_RenderPresent(renderer);

        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    continuer = 0;
                    break;

                case SDL_KEYDOWN:
                    switch (event.key.keysym.sym) {
                        case SDLK_ESCAPE:
                            continuer = 0;
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
    }

    // Libération des ressources
    LibererMap(&map, sprites);
    return 0;
}

void InitialiserSprites(Sprites* sprites, SDL_Renderer* renderer) {
    sprites[0].sprite = loadImage("img/sky.png", renderer);
    sprites[0].traverser = 1; // Le ciel est traversable

    sprites[1].sprite = loadImage("img/sol.png", renderer);
    sprites[1].traverser = 0; // Le sol n'est pas traversable

    sprites[2].sprite = loadImage("img/block.png", renderer);
    sprites[2].traverser = 0; // Le bloc de pierre n'est pas traversable

    sprites[3].sprite = loadImage("img/boite.png", renderer);
    sprites[3].traverser = 0; // La boîte n'est pas traversable

    sprites[4].sprite = loadImage("img/tuyau1.png", renderer);
    sprites[4].traverser = 0; // Tuyau partie 1

    sprites[5].sprite = loadImage("img/tuyau2.png", renderer);
    sprites[5].traverser = 0; // Tuyau partie 2

    sprites[6].sprite = loadImage("img/tuyau3.png", renderer);
    sprites[6].traverser = 0; // Tuyau partie 3

    sprites[7].sprite = loadImage("img/tuyau4.png", renderer);
    sprites[7].traverser = 0; // Tuyau partie 4

    sprites[8].sprite = loadImage("img/fin1.png", renderer);
    sprites[8].traverser = 0; // image fin 1 
    
    sprites[9].sprite = loadImage("img/fin2.png", renderer);
    sprites[9].traverser = 0; // image fin 2

    sprites[10].sprite = loadImage("img/", renderer);
    sprites[10].traverser = 0; //  goombas 1
    
    

}