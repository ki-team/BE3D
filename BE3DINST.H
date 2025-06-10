#ifndef INSTANCE_H
#define INSTANCE_H

#include <windows.h>
#include <SDL3/SDL.h>
#include "GAME.H"
#include <stdio.h>

#include "MAP.H"
#include "NODE.H"

typedef struct BE3DINST {
	// Windowing Objects
	SDL_Window* window;
	SDL_GLContext glContext;
	SDL_Event event;

	int x, y;					// Window resolution
	bool running;				// Mainloop Running Bool

	// DeltaTime
	float DeltaTime;
	float DLastTime;
	float DCurrTime;

	// Game stuff
	BE3DMAP activeMap;
	BE3DNODEF nodes[MAX];

	// Options
	bool vSync;
} BE3DINST;

void InitInstance(BE3DINST* inst)
{
	if (!SDL_Init(SDL_INIT_VIDEO)) {
		printf("!InitSDL : %s", SDL_GetError());
		return;
	}
	
	inst->x = GetSystemMetrics(SM_CXSCREEN);
	inst->y = GetSystemMetrics(SM_CYSCREEN);
	inst->window = SDL_CreateWindow("a", inst->x, inst->y, SDL_WINDOW_OPENGL | SDL_WINDOW_FULLSCREEN);
	inst->glContext = SDL_GL_CreateContext(inst->window);

	inst->running = true;
	SDL_ShowWindow(inst->window);
}

void ToggleVSync(BE3DINST inst) {
	if (inst.vSync) {
		inst.vSync = false;
		SDL_GL_SetSwapInterval(0);
	}
	if (!inst.vSync) {
		inst.vSync = true;
		SDL_GL_SetSwapInterval(1);
	}
}

void UpdateDeltaTimes(BE3DINST* inst)
{
	inst->DLastTime = inst->DCurrTime;
	inst->DCurrTime = SDL_GetTicks();
	inst->DeltaTime = inst->DLastTime - inst->DCurrTime;
}

#endif
