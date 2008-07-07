#ifndef BACKGROUND
#define BACKGROUND
#include "../../gorgon_core/include/gorgon.h"
#include "debug.h"
#define YAMATTO 0
typedef struct
{
	gorgonSound		*music;
	gorgonBackground	bg;
	gorgonBackgroundClsn	ladder;
	gorgonBackgroundClsn 	plataform;
}background;

int createBackground(background *bg,gorgonAudio *audio,int which);
int destroyBackground(background *bg);
int backgroundCollision(int x, int y, int width, int height, background *bg);
void drawClsn(BITMAP *layer,background *bg);
#endif
