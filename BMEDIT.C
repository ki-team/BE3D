#include <SDL3/SDL.h>
#include <imgui.h>

#define KEY event.key.scancode


int main() {
	SDL_Init(SDL_INIT_VIDEO);
	SDL_Window* wind = SDL_CreateWindow("BM Editor", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 640, 480, SDL_WINDOW_OPENGL);
	SDL_GLContext cont = SDL_GL_CreateContext(wind);
	SDL_Event event;

	float zoom;
	Uint8 running = 1;
	Uint8 view = 0;

	while (running) 
	{
		while (SDL_PollEvent(&event)) 
		{
			if (event.type = SDL_EVENT_QUIT) 
			{
				running = 0;
			}
			if (KEY == SDL_SCANCODE_M) {			// View Switcher
				if (view == 1) view = 0;
				if (view == 0) view = 1;
			}
		}


	}
}