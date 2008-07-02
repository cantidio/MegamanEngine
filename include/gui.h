#ifndef GUI
#define GUI
#include "player.h"
#include "weapon.h"
typedef struct
{
	gorgonSpritePack spritePack;
}megamanGui;

void createGui(megamanGui *gui);
void guiDraw(BITMAP *layer,megamanGui *gui,megaman *mega);
#endif
