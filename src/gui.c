#include "../include/gui.h"

void createGui(megamanGui *gui)
{
	gorgonLoadSpritePack(&gui->spritePack,"./resource/menu.spk");
}
void guiDraw(BITMAP *layer,megamanGui *gui,megaman *mega)
{
	short heightL	= gui->spritePack.sprite[71].image->h*((float)mega->life/MaxHealth);
	short destYL	= gui->spritePack.sprite[71].image->h-heightL;
	short heightW	= gui->spritePack.sprite[71].image->h*((float)mega->weapons.weapon[mega->weapons.weaponInUse].bar/maxWeaponBar);
	short destYW	= gui->spritePack.sprite[71].image->h-heightW;
	
	gorgonDrawSpriteByIndex(layer,&gui->spritePack,NULL,70,NORMAL,10,25);
	gorgonBlitSpriteByIndex(layer,&gui->spritePack,NULL,71,10,25,0,0,0,destYL,gui->spritePack.sprite[71].image->w,heightL);
	gorgonDrawSpriteByIndex(layer,&gui->spritePack,NULL,72,NORMAL,10,25);
	gorgonBlitSpriteByIndex(layer,&gui->spritePack,NULL,73,10,25,0,0,0,destYW,gui->spritePack.sprite[71].image->w,heightW);
	switch(mega->weapons.weaponInUse)
	{
		case plasmaShot:	gorgonDrawSpriteByIndex(layer,&gui->spritePack,NULL,7,NORMAL,10,25);	break;
		case boomerang:	gorgonDrawSpriteByIndex(layer,&gui->spritePack,NULL,1,NORMAL,10,25);	break;
		case iceBlast:		gorgonDrawSpriteByIndex(layer,&gui->spritePack,NULL,2,NORMAL,10,25);	break;
		case bombThower:	gorgonDrawSpriteByIndex(layer,&gui->spritePack,NULL,5,NORMAL,10,25);	break;
		case fireBlast:	gorgonDrawSpriteByIndex(layer,&gui->spritePack,NULL,0,NORMAL,10,25);	break;
		case thunderShot:	gorgonDrawSpriteByIndex(layer,&gui->spritePack,NULL,4,NORMAL,10,25);	break;
		case shadowBlade:	gorgonDrawSpriteByIndex(layer,&gui->spritePack,NULL,20,NORMAL,10,25);	break;
	}
}

void guiStatusDraw(BITMAP *layer,megamanGui *gui,megaman *mega)
{

}
void destroyGui(megamanGui *gui)
{
	gorgonDestroySpritePack(&gui->spritePack);
}
