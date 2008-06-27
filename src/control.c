#include "../include/control.h"

int createDefaultControl(inputControl *c)
{
	if(c!=NULL)
	{
		c->shot		= KEY_Q;
		c->jump		= KEY_A;
		c->weaponF	= KEY_W;
		c->weaponB	= KEY_S;
		c->start	= KEY_ENTER;
		c->up		= KEY_UP;
		c->right	= KEY_RIGHT;
		c->left		= KEY_LEFT;
		c->down		= KEY_DOWN;
		return 1;
	}
	return 0;
}
int saveControlDef(inputControl *c)
{
	FILE *file;
	file=fopen("control.bin","wb");
	if(file!=NULL)
	{
		fwrite(c,1,sizeof(inputControl),file);
		fclose(file);
		return 1;
	}
	return 0;
}
int loadControlDef(inputControl *c)
{
	FILE *file;
	inputControl *control;

	file=fopen("control.bin","rb");

	if(file!=NULL)
	{
		fread(control,1,sizeof(inputControl),file);
		*c=*control;
		fclose(file);
		return 1;
	}
	else
	{
		createDefaultControl(c);
		return saveControlDef(c);
	}
	return 0;
}
