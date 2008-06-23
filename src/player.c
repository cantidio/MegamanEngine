#include "../include/player.h"

/**
 * função para criar e setar todos os atributos do megaman
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 22/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @return: int
 */
int createMegaman(megaman *mega)
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
		mega->pal=NULL;
		//error=gorgonLoadPalette(&mega->pal,"./resource/megaman.act");
		if(error!=GORGON_OK) return error;
		mega->life				= MaxHealth;
		createDefaultControl(&mega->controlDef);
		mega->x					= 100;
		mega->y					= 200;
		mega->xPulse				= 0;
		mega->yPulse				= 0;
		mega->xPulseValue			= 1.5;
		mega->yPulseValue			= 1.5;
		mega->xPulseMax				= 3;
		mega->yPulseMax				= 6;
		mega->imortal				= 0;
		mega->control				= 1;
		mega->direction				= 1;
		mega->animationPlaying			= animStand;
		return createWeaponList(&mega->weapons);
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
int unloadMegaman(megaman *mega)
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
 */
void megamanChangeAnimation(megaman *mega,int anim)
{
	mega->animationPlaying=anim;
	mega->animationPack.animation[mega->animationPlaying].frameOn	=0;
	mega->animationPack.animation[mega->animationPlaying].timeOn	=0;
}
/**
 * função que muda a animação atual do megaman apenas se a animacao não estiver passando
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 21/06/2008
 * @final: 21/06/2008
 * @param: megaman *, ponteiro para o megaman
 */
void megamanChangAnimationIfChange(megaman *mega, int anim)
{
	if(mega->animationPlaying!=anim)
		megamanChangeAnimation(mega,anim);
}
/**
 * função que faz o megaman pular
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 21/06/2008
 * @final: 21/06/2008
 * @param: megaman *, ponteiro para o megaman
 */
void megamanJump(megaman *mega)
{
	//toca som de pulo
	mega->yPulse=-mega->yPulseMax;
	megamanChangeAnimation(mega,animJump);
}
/**
 * função para desenhar o megaman na tela
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 22/06/2008
 * @final: 22/06/2008
 * @param: BITMAP *, ponteiro para a superfície
 * @param: megaman *, ponteiro para o megaman
 */
void megamanDraw(BITMAP *layer, megaman *mega)
{

	//rect(layer,(int)mega->x,(int)mega->y,(int)mega->x+10,(int)mega->y+10,makecol(0,0,255));
	gorgonShowAnimation(layer,&mega->animationPack.animation[mega->animationPlaying],&mega->spritePack,mega->pal,mega->direction,(int)mega->x,(int)mega->y);
}
/**
 * função para mover o megaman no eixoX
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 22/06/2008
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
			if(mega->x+10<screen->w && backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
				mega->x++;
			else break;
		}
	}
	else if(mega->xPulse<0)
	{
		for(i=0; i<-mega->xPulse; i++)
		{
			if(mega->x-10>0 && backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
				mega->x--;
			else break;
		}
	}
}
/**
 * função para mover o megaman no eixoY
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 22/06/2008
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
			if(mega->y+10<screen->h && backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
				mega->y++;
			else break;
		}
	}
	else if(mega->yPulse<0)
	{
		for(i=0; i<-mega->yPulse; i++)
		{
			if(mega->y-10>0 && backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
				mega->y--;
			else break;
		}
	}
	if(backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))//colocar negado em colisão
		mega->yPulse+=mega->yPulseValue;
}
/**
 * função para fazer o megaman atirar
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 22/06/2008
 * @final: 22/06/2008
 * @param: megaman *, ponteiro para o megaman
 */
void megamanShot(megaman *mega)
{
}
/**
 * função que lida com os eventos básicos do megaman
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 21/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @return: int
 */
int megamanNormalEvents(megaman *mega,background *bg)
{


	if(mega->control)
	{
		if(key[mega->controlDef.shot])
		{
			//megamanShot(mega);
		}
		else if(key[mega->controlDef.jump] && key[mega->controlDef.down])
		{
			mega->animationPlaying=animSlide;
		}
		else if(key[mega->controlDef.jump])
		{
			if(backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
			{
				megamanJump(mega);
			}
		}
		else if(key[mega->controlDef.right])
		{
			mega->direction=NORMAL;
			if(mega->xPulse<mega->xPulseMax)
			{
				mega->xPulse+=mega->xPulseValue;
				if(backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
					megamanChangAnimationIfChange(mega,animWalk);
			}
		}
		else if(key[mega->controlDef.left])
		{
			mega->direction=H_FLIP;
			if(mega->xPulse>-mega->xPulseMax)
			{
				mega->xPulse-=mega->xPulseValue;
				if(backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
					megamanChangAnimationIfChange(mega,animWalk);
			}
		}
		else if(!key[mega->controlDef.right] && mega->xPulse>0)
		{
			megamanChangAnimationIfChange(mega,animStand);
			mega->xPulse-=mega->xPulseValue;
			if(mega->xPulse<0) mega->xPulse=0;
		}
		else if(!key[mega->controlDef.left] && mega->xPulse<0)
		{
			megamanChangAnimationIfChange(mega,animStand);
			mega->xPulse+=mega->xPulseValue;
			if(mega->xPulse>0) mega->xPulse=0;
		}
		if(key[mega->controlDef.weaponF])
		{
			nextWeapon(&mega->weapons);
		}
		else if(key[mega->controlDef.weaponB])
		{
			previousWeapon(&mega->weapons);
		}
	}
	megamanMoveX(mega,bg);
	megamanMoveY(mega,bg);


}

