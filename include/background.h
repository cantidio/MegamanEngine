#ifndef BACKGROUND
#define BACKGROUND
#include "../../gorgon_core/include/gorgon.h"

#define YAMATTO 0
typedef struct
{
	gorgonBackground	bg;
	gorgonBackgroundClsn	ladder;
	gorgonBackgroundClsn 	plataform;
}background;

int createBackground(background *bg,int which);
int destroyBackground(background *bg);
int backgroundCollision(int x, int y, int width, int height, background *bg);
int colisaoCenario(background *bg,int x,int y, int width, int height);
#endif
