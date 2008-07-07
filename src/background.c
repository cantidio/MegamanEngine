#include "../include/background.h"

int createBackground(background *bg,gorgonAudio *audio,int which)
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
			gorgonLoadSound(&bg->music,"./resource/background/yamatto.mp3",audio);
			break;
		//outros cenários
	}
	return error;
}
int destroyBackground(background *bg)
{
	gorgonDestroyBackground(&bg->bg);
	gorgonDestroyClsn(&bg->plataform.clsn);
}
/**
 * função para desenhar os obstáculos do cenário
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	04/07/2008
 * @final: 	04/07/2008
 * @param: 	BITMAP *, ponteiro para a superfície e ser desenhada
 * @param: 	background *, ponteiro para o cenário
 */
void drawClsn(BITMAP *layer,background *bg)
{
	if(debug)
	{
		int i;
		int x=bg->bg.posX;
		int y=bg->bg.posY;
		for(i=0; i<bg->plataform.clsn.boxNumber; i++)
		{
			rect(layer,x+bg->plataform.clsn.x1[i],y+bg->plataform.clsn.y1[i],x+bg->plataform.clsn.x2[i],y+bg->plataform.clsn.y2[i],makecol(0,0,255));
		}
	}
}
/**
 * função para calcular se houve ou não colisão com o cenário
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	23/06/2008
 * @final: 	04/07/2008
 * @param: 	int, posicao x
 * @param: 	int, posicao y
 * @param: 	int, largura
 * @param: 	int, altura
 * @param: 	background *, ponteiro para o cenário
 * @return:	int
 */
int backgroundCollision(int x, int y, int width, int height, background *bg)
{
	int i,j;
	if(width<0)	width*=-1;
	if(height<0)	height*=-1;
	for(i=0; i<bg->plataform.clsn.boxNumber; i++)
	{

		if
		(!(
			(bg->plataform.clsn.x1[i] > x + width) ||
			(bg->plataform.clsn.y1[i] > y + height) ||
			(bg->plataform.clsn.x2[i] < x) ||
			(bg->plataform.clsn.y2[i] < y)
		))
		{
			//if(DEBUG) printf("%d, %d!\n",til->tiles[i].posX[j],til->tiles[i].posY[j]);
			//if(atrito!=NULL) *atrito=til->tiles[i].atrito;
			return 1;
		 }
	}
	return 0;
}
