#include <SDL2/SDL.h>
#include <SDL2/SDL_image.h>
#include <stdio.h>
#include <stdlib.h>

#include "file.h"
#include "game.h"

// ligne de compilation gcc main.c file.c game.c event.c charactere.c -o mario -lSDL2main -lSDL2_image -lSDL2

int init(SDL_Window **window, SDL_Renderer **renderer, int w, int h);

int main(int argc, char *argv[])
{
	SDL_Window *fenetre = SDL_CreateWindow("la fenetre", 150, 150, 900, 900, SDL_WINDOW_SHOWN);
	if (fenetre == NULL)
	{
		perror("erreur");
		exit(0);
		return EXIT_FAILURE;
	}
	SDL_Renderer *renderer = SDL_CreateRenderer(fenetre, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		fprintf(stderr, "Erreur chargement image\n");
		SDL_DestroyRenderer(renderer);
		SDL_DestroyWindow(fenetre);
		SDL_Quit();
	}

	SDL_SetRenderDrawColor(renderer, 0, 0, 255, 0);
	SDL_RenderClear(renderer);
	SDL_Texture *image = loadImage("img/menu.jpg",renderer);
	SDL_RenderCopy(renderer, image, NULL, NULL);
	SDL_RenderPresent(renderer);

	SDL_Event event;

	int continuer = 1;
	
	while (SDL_PollEvent(&event) || continuer==1){
		switch (event.type)
		{
			case SDL_QUIT:
				continuer=0;
				break;
				case SDL_KEYDOWN;
				switch(event.key,keysye,)
		
		}
	}
		
	
		
	
	

	SDL_DestroyTexture(image);
	SDL_DestroyRenderer(renderer);
	SDL_DestroyWindow(fenetre);
	SDL_Quit();

	return 0;
}
