#include "../include/background.h"

int createBackground(background *bg,int which)
{
	int error;
	switch(which)
	{
		case YAMATTO:
			error=gorgonLoadBackground(&bg->bg,"./resource/background/yamatto.gbg");
			gorgonCreateClsn(&bg->plataform.clsn,10);
			gorgonSetClsnValues(&bg->plataform.clsn,0,0,415,160,239);
			gorgonSetClsnValues(&bg->plataform.clsn,1,192,383,128,159);
			gorgonSetClsnValues(&bg->plataform.clsn,2,416,479,112,159);
			gorgonSetClsnValues(&bg->plataform.clsn,3,480,575,144,239);
			gorgonSetClsnValues(&bg->plataform.clsn,4,704,767,192,239);
			gorgonSetClsnValues(&bg->plataform.clsn,5,736,767,0,239);
			gorgonSetClsnValues(&bg->plataform.clsn,6,256,719,0,31);
			gorgonSetClsnValues(&bg->plataform.clsn,7,448,543,32,63);
			gorgonSetClsnValues(&bg->plataform.clsn,8,288,383,80,95);
			gorgonSetClsnValues(&bg->plataform.clsn,9,608,671,112,127);
			break;
	}
	return error;
}
int destroyBackground(background *bg)
{
	gorgonDestroyBackground(&bg->bg);
	gorgonDestroyClsn(&bg->plataform.clsn);
}
int desenhacol(BITMAP *layer,background *bg)
{
	int i;
	int x=bg->bg.posX;
	int y=bg->bg.posY;
	for(i=0; i<bg->plataform.clsn.boxNumber; i++)
	{
		rect(layer,x+bg->plataform.clsn.x1[i],y+bg->plataform.clsn.y1[i],x+bg->plataform.clsn.x2[i],y+bg->plataform.clsn.y2[i],makecol(255,0,0));
	}
}
int backgroundCollision(int x, int y, int width, int height, background *bg)
{
	int i,j;
	for(i=0; i<bg->plataform.clsn.boxNumber; i++)
	{

		if
		(!(
			(bg->plataform.clsn.x1[i] + bg->bg.posX > x + width) ||
			(bg->plataform.clsn.y1[i] + bg->bg.posY> y + height) ||
			(bg->plataform.clsn.x2[i] + bg->bg.posX < x) ||
			(bg->plataform.clsn.y2[i] + bg->bg.posY < y)
		))
		{
			//if(DEBUG) printf("%d, %d!\n",til->tiles[i].posX[j],til->tiles[i].posY[j]);
			//if(atrito!=NULL) *atrito=til->tiles[i].atrito;
			return 1;
		 }
	}
	return 0;
}
