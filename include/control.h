#ifndef CONTROL
#define CONTROL
#include<allegro.h>

typedef struct
{
	int shot;
	int jump;
	int weaponF;
	int weaponB;
	int start;
	int right;
	int left;
	int down;
}inputControl;

int createDefaultControl(inputControl *c);
#endif
