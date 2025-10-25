#include <stdio.h>
#include <SDL2/SDL.h>


#define WIDTH 400
#define HEIGHT 400

void main(){
	SDL_Init(SDL_INIT_VIDEO);
	int opacity;
	SDL_Window *window;
	SDL_Renderer *renderer;
	SDL_Event event;

	window  = SDL_CreateWindow("keymouse", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, WIDTH, HEIGHT, SDL_WINDOW_ALLOW_HIGHDPI);
	renderer = SDL_CreateRenderer(window, -1, 0);
	opacity = SDL_SetWindowOpacity(window, 0.5f);

	SDL_SetRenderDrawBlendMode(renderer, SDL_BLENDMODE_BLEND);

	printf("Opacity: %d", opacity);

	int running = 1;
	while(running){
		while(SDL_PollEvent(&event)){
			switch(event.type){
				case SDL_QUIT:
					running = 0;
					break;
			}	
		}
		SDL_SetRenderDrawColor(renderer, 0, 0, 0, 0);
		SDL_RenderClear(renderer);

		SDL_RenderPresent(renderer);
		SDL_Delay(16);
	}
}
