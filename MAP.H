#ifndef MAP_H
#define MAP_H

#define MAX 255											// Temporary, This will be set to probably the 16-Bit integer limit later (65535, or something like that)
#include <stdio.h>

typedef struct BE3DWALL {
	float xs, ys;
	float xe, ye;
} BE3DWALL;

typedef struct BE3DPROP {
	float x, y;
	float rotation;
} BE3DPROP;

typedef struct BE3DSECT {
	int wallCount;
	BE3DWALL sectorWalls[MAX];
	float sector_Height;
} BE3DSECT;

typedef struct BE3DMAP {
	int mapPropCount;
	int mapSectorCount;
	BE3DSECT mapSectors[MAX];
	BE3DPROP mapProps[MAX];
	Uint8 mapStatus;									// Will return with value '1' if There are Map Read errors
} BE3DMAP;

// [Map System Prefixes]
// Sector: 00
// Wall  : 01
// Prop  : 10						
// ObId  : 11											// BE3DOBID is not yet implemented, This is what will allow functions to be attached to walls, props, and entire sectors
// 
// [Map Object Order]
// Sector: PREFIX, WALLCOUNT, WALLHEIGHT, SECTOR_INDEX, OBID, END_LINE
// Wall	 : PREFIX, XS, YS, XE, YE, SECTOR_INDEX, OBID, END_LINE
// Prop  : PREFIX, X, Y, ROTATION, OBID, END_LINE
// ObId  : PREFIX, FUNCTION_POINTER, END_LINE
//
// [Considerations]
// - Sectors are Always Defined First, ObIds Second, Walls Third, and Props Last
// - END_LINE is same as \n

BE3DMAP LoadMap(const char* filepath)
{
	BE3DMAP map;
	memset(&map, 0, sizeof(BE3DMAP)); // Clear map struct
	map.mapStatus = 0;

	FILE* file = fopen(filepath, "rb");
	if (!file) {
		map.mapStatus = 1;
		return map;
	}

	uint8_t prefix;
	int sectorIndex = -1;

	while (fread(&prefix, sizeof(uint8_t), 1, file)) {
		if ((prefix & 0xC0) == 0x00) {
			// Sector
			sectorIndex++;
			if (sectorIndex >= MAX) {
				map.mapStatus = 1;
				break;
			}
			BE3DSECT* sect = &map.mapSectors[sectorIndex];
			fread(&sect->wallCount, sizeof(int), 1, file);
			fread(&sect->sector_Height, sizeof(float), 1, file);
		}
		if ((prefix & 0xC0) == 0x40) {
			// Wall
			if (sectorIndex < 0 || map.mapSectors[sectorIndex].wallCount >= MAX) {
				map.mapStatus = 1;
				break;
			}
			BE3DWALL* wall = &map.mapSectors[sectorIndex].sectorWalls[map.mapSectors[sectorIndex].wallCount++];
			fread(&wall->xs, sizeof(float), 1, file);
			fread(&wall->ys, sizeof(float), 1, file);
			fread(&wall->xe, sizeof(float), 1, file);
			fread(&wall->ye, sizeof(float), 1, file);
		}
		if ((prefix & 0xC0) == 0x80) {
			// Prop
			if (map.mapPropCount >= MAX) {
				map.mapStatus = 1;
				break;
			}
			BE3DPROP* prop = &map.mapProps[map.mapPropCount++];
			fread(&prop->x, sizeof(float), 1, file);
			fread(&prop->y, sizeof(float), 1, file);
			fread(&prop->rotation, sizeof(float), 1, file);
		}
		/*else {
			// ObID or unknown
			map.mapStatus = 1;
			break;
		}*/
	}

	fclose(file);
	return map;
}

//
// Syntax for Map Loading : the main engine Object that handles everything from engine settings to windowing is a Struct called BE3DINST.
// Inside of BE3DINST is a BE3DMAP Object called activeMap, Map Loading is called by 'BE3DINST myInst; myInst.activeMap = LoadMap("myMap.bm")'
//

#endif