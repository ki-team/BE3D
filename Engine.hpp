#include "game.hpp"
#include "maps.hpp"
#include "link.hpp"

class Engine {
	SDL_Window* window;
	SDL_GLContext glContext;	// for 3D Map
	SDL_Renderer* renderer;     	// for Hud and things
	SDL_Event event;

	float deltaTime, curr, last;
	bool run;

	Game g;
	Map m;

	Engine() {
		if (!SDL_Init(SDL_INIT_VIDEO)) printf("%s", SDL_GetError());

		SDL_Rect r;
		SDL_GetDisplayBounds(SDL_GetPrimaryDisplay(), &r);

		this->window = SDL_CreateWindow(GAMENAME, r.w, r.h, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
		this->GLContext = SDL_GL_CreateContext(this->window);
		this->renderer = SDL_CreateRenderer(this->window, NULL);
	}
	~Engine() {
		SDL_GL_DeleteContext(glContext);
		SDL_DestroyWindow(window);
		SDL_Quit();
	}

	void Entrypoint() {
		while(this->run) {
			// DeltaTimes
			this->currTime = SDL_GetTicks();
			this->deltaTime = lastTime - currTime;
			this->lastTime = currTime;
			while(SDL_PollEvent()) {
				this->g.input();
				this->m.input();
			}
			this->g.periodic();
			this->m.periodic();
			// Rendering
			}
		}
	}
};
