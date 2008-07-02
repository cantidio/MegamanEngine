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
int createMegaman(megaman *mega,inputControl *control,gorgonAudio *audio)
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

		mega->pal	=(RGB **)malloc(sizeof(RGB *)*10);//aumentar conforme a necessidade
		mega->sound	=(gorgonSound **)malloc(sizeof(gorgonSound *)*10);//aumentar conforme a necessidade
		gorgonLoadPalette(&mega->pal[plasmaShot],	"resource/act/megaman.act");
		gorgonLoadPalette(&mega->pal[boomerang],	"resource/act/cutman.act");
		gorgonLoadPalette(&mega->pal[bombThower],	"resource/act/bomberman.act");
		gorgonLoadPalette(&mega->pal[thunderShot],	"resource/act/elecman.act");
		gorgonLoadPalette(&mega->pal[fireBlast],	"resource/act/fireman.act");
		gorgonLoadPalette(&mega->pal[iceBlast],	"resource/act/freezeman.act");
		
		gorgonLoadSound(&mega->sound[0],"./resource/sons/cai_chao.wav",audio);
		gorgonLoadSound(&mega->sound[1],"./resource/sons/mmse006.wav",audio);
		
		
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
void megamanDraw(BITMAP *layer, megaman *mega,background *bg)
{
	gorgonShowAnimation(layer,&mega->animationPack.animation[mega->animationPlaying],&mega->spritePack,mega->pal[mega->weapons.weaponInUse],mega->direction,mega->x+bg->bg.posX,mega->y+bg->bg.posY);
//	rect(layer,mega->x+5,mega->y-22,mega->x+7,mega->y-2,	makecol(0,255,0));
//	rect(layer,mega->x-5,mega->y-22,mega->x-7,mega->y-2,	makecol(255,255,0));
//	rect(layer,mega->x-5,mega->y-27,mega->x+5,mega->y-25,	makecol(0,255,255));
//	rect(layer,mega->x-5,mega->y-2,	mega->x+5,mega->y,	makecol(255,0,255));
	textprintf_ex(layer,font,10,210,makecol(255,255,255),-1,"posx: %f",mega->x);
	textprintf_ex(layer,font,10,220,makecol(255,255,255),-1,"posy: %f",mega->y);
	textprintf_ex(layer,font,10,230,makecol(255,255,255),-1,"life: %d",mega->life);
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
			if(mega->x+10<bg->bg.width && !backgroundCollision((int)mega->x+7,(int)mega->y-22, 2,20,bg))
			{
				if(mega->x>=screen->w/2 && bg->bg.posX>((screen->w)-bg->bg.width)) bg->bg.posX--;
				mega->x++;
			}
			else break;
		}
	}
	else if(mega->xPulse<0)
	{
		for(i=0; i<-mega->xPulse; i++)
		{
			if(mega->x-10>0 && !backgroundCollision((int)mega->x-7,(int)mega->y-22, 2,20,bg))
			{
				if((bg->bg.width-mega->x)>=screen->w/2 && bg->bg.posX<0) bg->bg.posX++;
				mega->x--;
			}
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
void megamanMoveY(megaman *mega,background *bg,gorgonAudio *audio)
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
					gorgonPlaySound(mega->sound[reachGround],audio,3);
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
	int 	x	= 0;
	int 	y	= 0;
	short stand	= 0;
	short walk	= 0;
	short inAir	= 0;
	switch(mega->weapons.weaponInUse)
	{
		case plasmaShot:
		case iceBlast:
		case fireBlast:
			x		= mega->x;
			y		= mega->y-15;
			stand		= animShotStand;
			walk		= animShotWalking;
			inAir		= animShotInAir;
			break;
		case boomerang:
			mega->xPulse	= 0;
			x		= mega->x;
			y		= mega->y-15;
			stand		= animThrowStand;
			walk		= animThrowStand;
			inAir		= animThrowInAir;
			break;
		case bombThower:
			mega->xPulse	= 0;
			x		= mega->x;
			y		= mega->y-15;
			stand		= animThrowStand;
			walk		= animThrowStand;
			inAir		= animThrowInAir;
			break;
		case thunderShot:
			mega->xPulse	= 0;//o problema
			x		= mega->x;
			y		= mega->y-10;
			stand		= animShotStand;
			walk		= animShotWalking;
			inAir		= animShotInAir;
			break;
	}
	switch(mega->animationPlaying)
	{
		case animStand:
			mega->control=0;
			megamanChangAnimationIfChange(mega,stand,0);
			weaponShot(&mega->weapons,x,y,mega->direction);
			break;
		case animWalk:
			megamanChangAnimationIfChange(mega,walk,mega->animationPack.animation[mega->animationPlaying].frameOn );
			weaponShot(&mega->weapons,x,y,mega->direction);
			break;
		case animJump: case animFall:
			mega->control=0;
			megamanChangAnimationIfChange(mega,inAir,0);
			weaponShot(&mega->weapons,x,y,mega->direction);
			break;
	}
}

void megamanAnimationFinishedEvents(megaman *mega)
{
	if(gorgonAnimationFinished(&mega->animationPack.animation[mega->animationPlaying]))
		switch(mega->animationPlaying)
		{
			case animArrive:
			case animShotStand:
			case animThrowStand:
			case animSlide:
				mega->control=1;
				megamanChangAnimationIfChange(mega,animStand,0);
				mega->xPulse=0;
				break;
			case animThrowInAir:
			case animShotInAir:
				mega->control=1;
				megamanChangAnimationIfChange(mega,animFall,0);
				break;
		}
}
void megamanAnimationRunnigEvents(megaman *mega)
{
	if(mega->animationPlaying==animShotWalking)
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
		
	}
}
/**
 * função que lida com os eventos básicos do megaman
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 01/07/2008
 * @param: megaman *, ponteiro para o megaman
 * @return: int
 */
int megamanNormalEvents(megaman *mega,background *bg,gorgonAudio *audio)
{
	if(mega->control)
	{
		if(key[mega->controlDef.jump] && key[mega->controlDef.down] && backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
		{
			mega->control=0;
			megamanChangAnimationIfChange(mega,animSlide,0);
		}
		else if(key[mega->controlDef.shot] && canShot(&mega->weapons))
		{
			gorgonPlaySound(mega->sound[soundShot],audio,3);
			megamanShot(mega);
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
	
	megamanAnimationFinishedEvents(mega);
	megamanAnimationRunnigEvents(mega);
	megamanMoveX(mega,bg);
	megamanMoveY(mega,bg,audio);
}

