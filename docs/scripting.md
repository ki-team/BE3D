# Intro to Scripting


Below is the default Node Script. The Init() and Update() Functions cannot be removed as of Version 0.1
```
#include "BE3D_Develop.h"		// Development Header, Includes Everything inside the Engine

int Update() 
{
	// Calls Every single Frame
}

int Init()
{
	// Calls at the Begining of the Game
}
```
This is a similar layout to the Unity and Unreal Systems, Except with different names.
Unreal would have the Equivalent of Event Tick and Event Start, Unity has void types for Start and Update.