#include <SDL3/SDL.h>
#include <SDL3/SDL_image.h>
#include <SDL3/SDL_ttf.h>
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <gl/GL.h>
#include <gl/GLU.h>
#include <stdbool.h>

#include "BE3DINST.H"
#include "GAME.H"

#define KEYSTATUS inst.event.key.scancode

int main(int argc, char* argv[])
{
	BE3DINST inst;
	InitInstance(&inst);

	while (inst.running) 
	{
		UpdateDeltaTimes(&inst);

		while (SDL_PollEvent(&inst.event)) 
		{
			if (inst.event.type == SDL_EVENT_QUIT) {
				inst.running = false;
			}
			if (KEYSTATUS == SDL_SCANCODE_ESCAPE) {
				inst.running = false;
			}
			if (KEYSTATUS == SDL_SCANCODE_V) {
				ToggleVSync(inst);
			}
		}
		GAME_MapManager(&inst);
	}
	// Cleanup
	


	// GAME_cleanup(); Game Cleanup Process
}