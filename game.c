#include "game.h"
#include "file.h"
#include "charactere.h"
#include "event.h"



int jouer(SDL_Renderer* renderer) {
      
     //charger image et personnage. 

     SDL_Texture *image = loadImage("img/mario.png",renderer);
     SDL_RenderCopy(renderer, image, NULL, NULL);
if (image=NULL) {
printf("Erreur de chargement de Mario : %s\n", SDL_GetError());
exit(1);
}

     
    // Initialisation des variables
    int continuer = 1; // À utiliser pour savoir si on continue la boucle du jeu ou si on arrête
    SDL_Event event;  // Déclaration de l'événement

    // Configuration de la couleur de fond (blanc)
    SDL_SetRenderDrawColor(renderer, 255, 255, 255, 0);
   
    while(continuer) { // Coeur du jeu ici, les actions seront répétées pour faire le déplacement des différentes images, etc.
        SDL_RenderClear(renderer);

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

                        default:
                            break;
                    }
                    break;

                default:
                    break;
            }
        }

        // À ce stade, tu devrais dessiner et mettre à jour les objets du jeu
        // Afficher la scène et mettre à jour l'écran
        SDL_RenderPresent(renderer);

    }

    // Libération des ressources une fois le jeu terminé
    // LibererMap(map, sprites);   // Décommenter et compléter cette ligne selon ton code
    // freePersonnage(mario, goomba, nbGoomba);  // Libérer la mémoire allouée pour les personnages

    return continuer;  // Retourne la valeur de "continuer" pour quitter ou non
}