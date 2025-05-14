#include "game.h"
#include "file.h"
#include "charactere.h"
#include "event.h"

void AfficherMapAvecScrolling(Map* map, Sprites* sprites, SDL_Renderer* renderer, int xscroll) {
    int startCol = xscroll / Size_Sprite; // Colonne de départ
    int endCol = startCol + (LARGEUR_FENETRE / Size_Sprite) + 2; // Colonne de fin (+2 pour éviter les artefacts)

    if (endCol > map->width) {
        endCol = map->width; // Empêcher de dépasser la largeur de la map
    }

    for (int i = 0; i < map->height; i++) {
        for (int j = startCol; j < endCol; j++) {
            int spriteIndex = map->LoadedMap[i][j];
            if (spriteIndex >= 0 && spriteIndex < NbSprites) {
                SDL_Rect dest = { (j * Size_Sprite) - xscroll, i * Size_Sprite, Size_Sprite, Size_Sprite };
                SDL_RenderCopy(renderer, sprites[spriteIndex].sprite, NULL, &dest);
            }
        }
    }
}

int jouer_niveau1(SDL_Renderer* renderer) {
    // Charger la map niveau1
    Map map = {0};
    LireLevel1(&map);

    // Initialisation des sprites
    Sprites sprites[NbSprites];
    InitialiserSprites(sprites, renderer);

    // Variables pour Mario
    SDL_Event event;
    int continuer = 1;
    int marioX = 100;
    int marioY = 800; // Position initiale de Mario
    int marioVelY = 0;
    int scrollX = 0;
    int frame = 0;
    int dir = 1;
    int onGround = 0;

    while (continuer) {
        // Gestion des événements
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT || 
                (event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)) {
                continuer = 0;
            }
        }

        // Gestion des touches
        const Uint8 *state = SDL_GetKeyboardState(NULL);
        int moving = 0;
        int vitesseX = 0;
        if (state[SDL_SCANCODE_RIGHT]) {
            vitesseX = 4;
            dir = 1;
            moving = 1;
        } else if (state[SDL_SCANCODE_LEFT]) {
            vitesseX = -4;
            dir = -1;
            moving = 1;
        }

        if (moving) frame = (frame + 1) % 3;

        // Gestion des collisions horizontales
        int futureX = marioX + vitesseX;
            int midY = marioY + 20;
            int tileX = (futureX + 20) / Size_Sprite;
            int tileY = midY / Size_Sprite;

if (tileX >= 0 && tileX < map.width && tileY >= 0 && tileY < map.height) {
    int spriteIndex = map.LoadedMap[tileY][tileX];
    if (spriteIndex >= 0 && spriteIndex < NbSprites && sprites[spriteIndex].traverser) {
        marioX = futureX; // Mario peut avancer librement
    }
}
        // Gestion du saut
        if (onGround && state[SDL_SCANCODE_SPACE]) {
            marioVelY = -15; // Vitesse de saut
            onGround = 0;
        }

        // Gestion de la gravité
        marioVelY += 1; // Gravité
        if (marioVelY > 10) marioVelY = 10; // Limite de vitesse de chute
        int futureY = marioY + marioVelY;
        int futureTileX = (marioX + 20) / Size_Sprite;
        int futureTileY = (futureY + 39) / Size_Sprite;

        if (futureTileX >= 0 && futureTileX < map.width && futureTileY >= 0 && futureTileY < map.height) {
            int spriteIndex = map.LoadedMap[futureTileY][futureTileX];
            if (spriteIndex >= 0 && spriteIndex < NbSprites && sprites[spriteIndex].traverser) {
                marioY = futureY;
                onGround = 0;
            } else {
                marioVelY = 0;
                onGround = 1;
            }
        }

        // Gestion du scrolling
        scrollX = marioX - LARGEUR_FENETRE / 2;
        if (scrollX < 0) scrollX = 0;
        if (scrollX > map.width * Size_Sprite - LARGEUR_FENETRE) {
            scrollX = map.width * Size_Sprite - LARGEUR_FENETRE;
        }

        // Affichage
        SDL_RenderClear(renderer);

        // Afficher la map avec scrolling
        AfficherMapAvecScrolling(&map, sprites, renderer, scrollX);

        // Afficher Mario
        SDL_Rect marioRect = { marioX - scrollX, marioY, Size_Sprite, Size_Sprite };
        SDL_RenderCopy(renderer, sprites[1].sprite, NULL, &marioRect); // Utilisez un sprite pour Mario

        SDL_RenderPresent(renderer);
        SDL_Delay(16); // Limiter à ~60 FPS
    }

    // Libération des ressources
    LibererMap(&map, sprites);
    return 0;
}

void InitialiserSprites(Sprites* sprites, SDL_Renderer* renderer) {
    sprites[0].sprite = loadImage("img/sky.png", renderer);
    sprites[0].traverser = 1; // Le ciel est traversable

    sprites[1].sprite = loadImage("img/sol.png", renderer);
    sprites[1].traverser = 1; // Le sol est traversable

    sprites[2].sprite = loadImage("img/block.png", renderer);
    sprites[2].traverser = 1; // Le bloc de pierre est traversable

    sprites[3].sprite = loadImage("img/boite.png", renderer);
    sprites[3].traverser = 1; // La boîte est traversable

    sprites[4].sprite = loadImage("img/tuyau1.png", renderer);
    sprites[4].traverser = 1; // Tuyau partie 1 est traversable

    sprites[5].sprite = loadImage("img/tuyau2.png", renderer);
    sprites[5].traverser = 1; // Tuyau partie 2 est traversable

    sprites[6].sprite = loadImage("img/tuyau3.png", renderer);
    sprites[6].traverser = 1; // Tuyau partie 3 est traversable

    sprites[7].sprite = loadImage("img/tuyau4.png", renderer);
    sprites[7].traverser = 1; // Tuyau partie 4 est traversable

    sprites[8].sprite = loadImage("img/fin1.png", renderer);
    sprites[8].traverser = 1; // Image fin 1 est traversable

    sprites[9].sprite = loadImage("img/fin2.png", renderer);
    sprites[9].traverser = 1; // Image fin 2 est traversable

    sprites[10].sprite = loadImage("img/sky.png", renderer);
    sprites[10].traverser = 1; // Goombas 1 est traversable
}