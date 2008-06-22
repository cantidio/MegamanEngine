#include "../include/player.h"

/**
 * função para criar e setar todos os atributos do megaman
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 21/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @return: int
 */
int createMegaman(megaman *mega)
{
	int error;
	if(mega!=NULL)
	{
		mega->life				= MaxHealth;
		error=gorgonLoadSpritePack(&mega->spritePack,"./resource/megaman.spk");
		if(error!=GORGON_OK) return error;
		error=gorgonLoadAnimationPack(&mega->animationPack,"./resource/megaman.apk");
		if(error!=GORGON_OK) return error;
		error=gorgonMakeAnimationPackIndexes(&mega->animationPack,&mega->spritePack);
		if(error!=GORGON_OK) return error;
		mega->pal=NULL;
		//error=gorgonLoadPalette(&mega->pal,"./resource/megaman.act");
		if(error!=GORGON_OK) return error;
		mega->x					= 100;
		mega->y					= 200;
		mega->xPulse				= 0;
		mega->yPulse				= 0;
		mega->xPulseValue			= 1.5;
		mega->yPulseValue			= 1.5;
		mega->xPulseMax				= 6;
		mega->yPulseMax				= 6;
		mega->imortal				= 0;
		mega->control				= 0;
		mega->direction				= 1;
		mega->animationPlaying			= 1;
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
	mega->control		= 0;
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
	mega->animationPack.animation[mega->animationPlaying].frameOn=0;
	mega->animationPack.animation[mega->animationPlaying].timeOn=0;
}
/**
 * função que muda a animação atual do megaman apenas se fe a animacao n estiver passando
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
	mega->yPulse=mega->yPulseMax;
	megamanChangeAnimation(mega,animJump);
}

void megamanDraw(BITMAP *layer, megaman *mega)
{

	rect(layer,(int)mega->x,(int)mega->y,(int)mega->x+10,(int)mega->y+10,makecol(0,0,255));
	gorgonShowAnimation(&mega->animationPack.animation[mega->animationPlaying],&mega->spritePack,layer,mega->pal,(int)mega->x,(int)mega->y);
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
	if(mega!=NULL)
	{
		if(mega->control)
		{
			if(key[ATIRA])
			{
				//megamanShot(mega);
			}
			else if(key[PULA])
			{
				if(backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
				{
					megamanJump(mega);
				}
			}
			else if(key[FRENTE])
			{
				mega->direction=1;
				if(mega->xPulse<mega->xPulseMax)
				{
					mega->xPulse+=mega->xPulseValue;
					if(backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
						megamanChangAnimationIfChange(mega,animWalk);
				}
			}
			else if(key[TRAZ])
			{
				mega->direction=-1;
				if(mega->xPulse>-mega->xPulseMax)
				{
					mega->xPulse-=mega->xPulseValue;
					if(backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
						megamanChangAnimationIfChange(mega,animWalk);
				}
			}
			else if(!key[FRENTE] && mega->xPulse>0)
			{
				megamanChangAnimationIfChange(mega,animStand);
				mega->xPulse-=mega->xPulseValue;
				if(mega->xPulse<0) mega->xPulse=0;
			}
			else if(!key[TRAZ] && mega->xPulse<0)
			{
				megamanChangAnimationIfChange(mega,animStand);
				mega->xPulse+=mega->xPulseValue;
				if(mega->xPulse>0) mega->xPulse=0;
			}
			if(key[ARMAF])
			{
				nextWeapon(&mega->weapons);
			}
			else if(key[ARMAB])
			{
				previousWeapon(&mega->weapons);
			}
		}


		return 1;
	}
	return 0;
}

