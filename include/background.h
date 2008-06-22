#ifndef BACKGROUND
#define BACKGROUND
#include "../../gorgon_core/include/gorgon.h"
typedef struct
{
	gorgonBackground bg;
}background;

int createBackground(background *bg);
int backgroundCollision(int x, int y, int width, int height, background *bg);
#endif
