#ifndef GAME_H
#define GAME_H

#define GAMENAME	"GAME NAME HERE"
#define GAMEVER		1 
#define GAMEDEV		"Developer Name Here"

#include "BE3DINST.H"

// Handle Map Switching
void GAME_MapManager(BE3DINST* inst);

// Unity Update() or Unreal's Event Tick Equivalent
void GAME_Periodic(BE3DINST* inst);

// Initialization
void GAME_Init(BE3DINST* inst);


void GAME_Input() {

}

#endif