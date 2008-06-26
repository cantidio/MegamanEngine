#include "../include/player.h"

/**
 * função para criar e setar todos os atributos do megaman
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 26/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @return: int
 */
int createMegaman(megaman *mega,inputControl *control)
{
	int error;
	if(mega!=NULL)
	{
		error=gorgonLoadSpritePack(&mega->spritePack,"./resource/megaman.spk");
		if(error!=GORGON_OK) return error;
		error=gorgonLoadAnimationPack(&mega->animationPack,"./resource/megaman.apk");
		if(error!=GORGON_OK) return error;
		error=gorgonMakeAnimationPackIndexes(&mega->animationPack,&mega->spritePack);
		if(error!=GORGON_OK) return error;
		mega->pal=(RGB **)malloc(sizeof(RGB *)*10);//aumentar conforme a necessidade
		gorgonLoadPalette(&mega->pal[0],"resource/act/megaman.act");
		gorgonLoadPalette(&mega->pal[1],"resource/act/cutman.act");
		gorgonLoadPalette(&mega->pal[2],"resource/act/bomberman.act");
		gorgonLoadPalette(&mega->pal[3],"resource/act/elecman.act");
		gorgonLoadPalette(&mega->pal[4],"resource/act/fireman.act");
		//error=gorgonLoadPalette(&mega->pal,"./resource/megaman.act");
		if(error!=GORGON_OK) return error;
		mega->life				= MaxHealth;
		mega->controlDef			= *control;
		mega->x					= 20;
		mega->y					= -40;
		mega->xPulse				= 0;
		mega->yPulse				= 0;
		mega->xPulseValue			= 1.5;
		mega->yPulseValue			= 1.5;
		mega->xPulseMax				= 3;
		mega->yPulseMax				= 6;
		mega->imortal				= 0;
		mega->control				= 0;
		mega->direction				= NORMAL;
		mega->animationPlaying			= animTeleport;
		return createAllWeapons(&mega->weapons);
	}
	return 0;
}
/**
 * função para descarregar a memória ocupada pelo megaman
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 22/06/2008
 * @final: 22/06/2008
 * @param: megaman *,ponteiro para o megaman
 * @return: int gorgon_error
 */
int destroyMegaman(megaman *mega)
{
	int error;
	mega->life		= 0;
	mega->xPulse		= 0;
	mega->yPulse		= 0;
	mega->xPulseValue	= 0;
	mega->yPulseValue	= 0;
	mega->xPulseMax		= 0;
	mega->yPulseMax		= 0;
	mega->imortal		= 0;
	mega->control		= 1;
	mega->direction		= 0;
	mega->animationPlaying	= 0;
	error=gorgonDestroySpritePack(&mega->spritePack);
	if(error!=GORGON_OK) return error;
	return gorgonDestroyAnimationPack(&mega->animationPack);
}
/**
 * função que muda a animação atual do megaman
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 21/06/2008
 * @final: 21/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @param: int, número da animação que irá mudar
 * @param: int, número do frame da animação que irá começar
 */
void megamanChangeAnimation(megaman *mega,int anim,int frame)
{
	mega->animationPlaying=anim;
	mega->animationPack.animation[mega->animationPlaying].frameOn	= frame;
	mega->animationPack.animation[mega->animationPlaying].timeOn	= 0;
}
/**
 * função que muda a animação atual do megaman apenas se a animacao não estiver passando
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 21/06/2008
 * @final: 21/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @param: int, número da animaçao para mudar
 * @param: int, número do frame que a animação deve começar
 */
void megamanChangAnimationIfChange(megaman *mega, int anim,int frame)
{
	if(mega->animationPlaying!=anim)
		megamanChangeAnimation(mega,anim,frame);
}
/**
 * função que faz o megaman pular
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 21/06/2008
 * @final: 25/06/2008
 * @param: megaman *, ponteiro para o megaman
 */
void megamanJump(megaman *mega)
{
	//toca som de pulo
	mega->y-=2;
	mega->yPulse=-2*mega->yPulseMax;
	megamanChangeAnimation(mega,animJump,0);
}
/**
 * função para desenhar o megaman na tela
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 22/06/2008
 * @final: 25/06/2008
 * @param: BITMAP *, ponteiro para a superfície
 * @param: megaman *, ponteiro para o megaman
 */
void megamanDraw(BITMAP *layer, megaman *mega)
{
	gorgonShowAnimation(layer,&mega->animationPack.animation[mega->animationPlaying],&mega->spritePack,mega->pal[mega->weapons.weaponInUse],mega->direction,(int)mega->x,(int)mega->y);
//	rect(layer,mega->x+5,mega->y-22,mega->x+7,mega->y-2,	makecol(0,255,0));
//	rect(layer,mega->x-5,mega->y-22,mega->x-7,mega->y-2,	makecol(255,255,0));
//	rect(layer,mega->x-5,mega->y-27,mega->x+5,mega->y-25,	makecol(0,255,255));
//	rect(layer,mega->x-5,mega->y-2,	mega->x+5,mega->y,	makecol(255,0,255));
}
/**
 * função para mover o megaman no eixoX
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 22/06/2008
 * @final: 25/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @param: background *, ponteiro para o cenário
 */
void megamanMoveX(megaman *mega,background *bg)
{
	int i;
	
	if(mega->xPulse>0)
	{
		for(i=0; i<mega->xPulse; i++)
		{
			if(mega->x+10<screen->w && !backgroundCollision((int)mega->x+7,(int)mega->y-22, 2,20,bg))
				if(mega->x>=screen->w/2 && bg->bg.posX>((screen->w)-bg->bg.width)) bg->bg.posX--;
					else mega->x++;
			else break;
		}
	}
	else if(mega->xPulse<0)
	{
		for(i=0; i<-mega->xPulse; i++)
		{
			if(mega->x-10>0 && !backgroundCollision((int)mega->x-7,(int)mega->y-22, 2,20,bg))
				if(mega->x<=screen->w/2 && bg->bg.posX<0) bg->bg.posX++;
					else mega->x--;
			else break;
		}
	}
}
/**
 * função para mover o megaman no eixoY
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 22/06/2008
 * @final: 25/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @param: background *, ponteiro para o cenário
 */
void megamanMoveY(megaman *mega,background *bg)
{
	int i;
	if(mega->yPulse>0)
	{
		for(i=0; i<mega->yPulse; i++)
		{
			if(!backgroundCollision((int)mega->x-5,(int)mega->y-2, 10,2,bg))
				mega->y++;
			else
			{
				mega->yPulse=0;
				if(mega->animationPlaying==animTeleport)
					megamanChangAnimationIfChange(mega,animArrive,0);
				else
				{
					megamanChangAnimationIfChange(mega,animStand,0);
					mega->control=1;
				}
				break;
			}
		}
	}
	else if(mega->yPulse<0)
	{
		for(i=0; i<-mega->yPulse; i++)
		{
			if(!backgroundCollision((int)mega->x-5,(int)mega->y-27, 10,2,bg))
				mega->y--;
			else
			{
				mega->yPulse=0;
				break;
			}
		}
	}
	if(!backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
	{
		mega->yPulse+=mega->yPulseValue;
		if(mega->control && mega->yPulse>0) megamanChangAnimationIfChange(mega,animFall,0);
	}
}
/**
 * função para fazer o megaman atirar
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 22/06/2008
 * @final: 26/06/2008
 * @param: megaman *, ponteiro para o megaman
 */
void megamanShot(megaman *mega)
{
	switch(mega->animationPlaying)
	{
		case animStand:
			mega->control=0;
			megamanChangAnimationIfChange(mega,animShotStand,0);
			weaponShot(&mega->weapons,mega->x,mega->y-10,mega->direction);
			break;
		case animWalk:
			megamanChangAnimationIfChange(mega,animShotWalking,mega->animationPack.animation[mega->animationPlaying].frameOn-1);
			break;
		case animJump: case animFall:
			megamanChangAnimationIfChange(mega,animShotInAir,0);
			break;
	}
}
/**
 * função que lida com os eventos básicos do megaman
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 25/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @return: int
 */
int megamanNormalEvents(megaman *mega,background *bg)
{
	if(mega->control)
	{
		if(key[mega->controlDef.shot])
		{
			megamanShot(mega);
		}
		else if(key[mega->controlDef.jump] && key[mega->controlDef.down] && backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
		{
			mega->control=0;
			megamanChangAnimationIfChange(mega,animSlide,0);
		}
		else if(key[mega->controlDef.jump] && backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
		{
				megamanJump(mega);
		}
		else if(key[mega->controlDef.right])
		{
			mega->direction=NORMAL;
			if(backgroundCollision((int)mega->x-5,(int)mega->y-2, 10,2,bg))
				megamanChangAnimationIfChange(mega,animWalk,0);
			if(mega->xPulse<mega->xPulseMax)
			{
				mega->xPulse+=mega->xPulseValue;
			}
		}
		else if(key[mega->controlDef.left])
		{
			mega->direction=H_FLIP;
			if(backgroundCollision((int)mega->x-5,(int)mega->y-2, 10,2,bg))
				megamanChangAnimationIfChange(mega,animWalk,0);
			if(mega->xPulse>-mega->xPulseMax)
			{
				mega->xPulse-=mega->xPulseValue;
			}
		}
		else if(!key[mega->controlDef.right] && mega->xPulse>0)
		{
			megamanChangAnimationIfChange(mega,animStand,0);
			mega->xPulse-=mega->xPulseValue;
			if(mega->xPulse<0) mega->xPulse=0;
		}
		else if(!key[mega->controlDef.left] && mega->xPulse<0)
		{
			megamanChangAnimationIfChange(mega,animStand,0);
			mega->xPulse+=mega->xPulseValue;
			if(mega->xPulse>0) mega->xPulse=0;
		}
		if(key[mega->controlDef.weaponF])
		{
			nextWeapon(&mega->weapons);
			key[mega->controlDef.weaponF]=0;
		}
		else if(key[mega->controlDef.weaponB])
		{
			previousWeapon(&mega->weapons);
			key[mega->controlDef.weaponB]=0;
		}
	}

	if(mega->animationPlaying==animShotStand && gorgonAnimationFinished(&mega->animationPack.animation[mega->animationPlaying]))
	{
		mega->control=1;
		megamanChangAnimationIfChange(mega,animStand,0);
	}
	else if(mega->animationPlaying==animShotWalking)
	{
	
	}
	else if(mega->animationPlaying==animShotInAir)
	{
	
	}
	else if(mega->animationPlaying==animSlide)
	{
		if(mega->direction==NORMAL)
			mega->xPulse=mega->xPulseValue*4;
		else
			mega->xPulse=-mega->xPulseValue*4;
		if(gorgonAnimationFinished(&mega->animationPack.animation[mega->animationPlaying]))
		{
			mega->control=1;
			megamanChangAnimationIfChange(mega,animStand,0);
		}
	}
	else if(mega->animationPlaying==animArrive && gorgonAnimationFinished(&mega->animationPack.animation[mega->animationPlaying]))
	{
		mega->control=1;
		megamanChangAnimationIfChange(mega,animStand,0);
	}
	
	megamanMoveX(mega,bg);
	megamanMoveY(mega,bg);
}

