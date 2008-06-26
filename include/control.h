#ifndef CONTROL
#define CONTROL
#include<allegro.h>
#include<stdio.h>
typedef struct
{
	int shot;
	int jump;
	int weaponF;
	int weaponB;
	int start;
	int up;
	int right;
	int left;
	int down;
}inputControl;

int createDefaultControl(inputControl *c);
int saveControlDef(inputControl *c);
int loadControlDef(inputControl *c);
#endif
