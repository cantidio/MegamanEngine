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
		c->right	= KEY_RIGHT;
		c->left		= KEY_LEFT;
		c->down		= KEY_DOWN;
		return 1;
	}
	return 0;
}
