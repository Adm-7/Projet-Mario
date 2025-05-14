#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "game.h"

// Ligne de compilation :
// gcc main.c file.c game.c event.c charactere.c -o mario -lSDL2main -lSDL2_image -lSDL2

int main(int argc, char *argv[]) {
    // Initialisation de SDL
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "Erreur SDL_Init : %s\n", SDL_GetError());
        return EXIT_FAILURE;
    }

    // Initialisation de SDL_image
    if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG)) {
        fprintf(stderr, "Erreur IMG_Init : %s\n", IMG_GetError());
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Définir les dimensions de la fenêtre
    int screenWidth = 1000;  // Largeur de la fenêtre
    int screenHeight = 1000; // Hauteur de la fenêtre

    // Créer une fenêtre en mode fenêtré
    SDL_Window *fenetre = SDL_CreateWindow(
        "la fenetre",
        SDL_WINDOWPOS_CENTERED,
        SDL_WINDOWPOS_CENTERED,
        LARGEUR_FENETRE,
        HAUTEUR_FENETRE,
        0 // Mode fenêtré
    );
    if (fenetre == NULL) {
        fprintf(stderr, "Erreur SDL_CreateWindow : %s\n", SDL_GetError());
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Créer un renderer
    SDL_Renderer *renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
    if (!renderer) {
        fprintf(stderr, "Erreur SDL_CreateRenderer : %s\n", SDL_GetError());
        SDL_DestroyWindow(fenetre);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    // Couleur de fond
    SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
    SDL_RenderClear(renderer);

    // Charger l'image du menu
    SDL_Texture *image = loadImage("img/menu.jpg", renderer);
    SDL_Texture *creditsTexture = loadImage("img/Credits.jpg", renderer);
    if (image == NULL) {
        fprintf(stderr, "Erreur chargement image : %s\n", SDL_GetError());
        SDL_DestroyRenderer(renderer);
        SDL_DestroyWindow(fenetre);
        IMG_Quit();
        SDL_Quit();
        return EXIT_FAILURE;
    }

    SDL_Event event; // Déclaration de la variable event
    SDL_RenderCopy(renderer, image, NULL, NULL);
    SDL_RenderPresent(renderer);

    int continuer = 1;

    while (continuer) {
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
                        case SDLK_1:
                            jouer(renderer); // Ap
                            continuer = 0;
                            SDL_Log("Appuie sur la touche 1");
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
    SDL_DestroyTexture(image);
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(fenetre);
    IMG_Quit();
    SDL_Quit();

    return 0;
}