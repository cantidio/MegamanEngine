#include "../include/player.h"

/**
 * função para criar e setar todos os atributos do megaman
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	18/06/2008
 * @final: 	26/06/2008
 * @param: 	megaman *, ponteiro para o megaman
 * @return:	int
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
		mega->audio	= *audio;
		mega->pal	=(RGB **)malloc(sizeof(RGB *)*30);//aumentar conforme a necessidade
		mega->sound	=(gorgonSound **)malloc(sizeof(gorgonSound *)*10);//aumentar conforme a necessidade
		gorgonLoadPalette(&mega->pal[plasmaShot],	"resource/act/megaman.act");
		gorgonLoadPalette(&mega->pal[boomerang],	"resource/act/cutman.act");
		gorgonLoadPalette(&mega->pal[bombThower],	"resource/act/bomberman.act");
		gorgonLoadPalette(&mega->pal[thunderShot],	"resource/act/elecman.act");
		gorgonLoadPalette(&mega->pal[fireBlast],	"resource/act/fireman.act");
		gorgonLoadPalette(&mega->pal[iceBlast],		"resource/act/freezeman.act");
		gorgonLoadPalette(&mega->pal[shadowBlade],	"resource/act/yamattoman.act");
		gorgonLoadSound(&mega->sound[0],"./resource/sons/cai_chao.wav",&mega->audio);
		gorgonLoadSound(&mega->sound[1],"./resource/sons/mmse006.wav",&mega->audio);
		gorgonLoadSound(&mega->sound[2],"./resource/sons/mmse032.wav",&mega->audio);
		
		if(error!=GORGON_OK) return error;
		mega->life				= MaxHealth;
		mega->controlDef			= *control;
		mega->lastShot				= 0;
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
		return createAllWeapons(&mega->weapons,audio);
	}
	return 0;
}
/**
 * função para descarregar a memória ocupada pelo megaman
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	22/06/2008
 * @final: 	22/06/2008
 * @param: 	megaman *,ponteiro para o megaman
 * @return:	int gorgon_error
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
	
	gorgonDestroyPalette(&mega->pal[plasmaShot]);
	gorgonDestroyPalette(&mega->pal[boomerang]);
	gorgonDestroyPalette(&mega->pal[bombThower]);
	gorgonDestroyPalette(&mega->pal[thunderShot]);
	gorgonDestroyPalette(&mega->pal[fireBlast]);
	gorgonDestroyPalette(&mega->pal[iceBlast]);
	
	gorgonDestroySound(mega->sound[0]);
	gorgonDestroySound(mega->sound[1]);
	free(mega->sound);
	destroyWeaponList(&mega->weapons);
	error=gorgonDestroySpritePack(&mega->spritePack);
	if(error!=GORGON_OK) return error;
	return gorgonDestroyAnimationPack(&mega->animationPack);
}

/**
 * função que muda a animação atual do megaman
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	21/06/2008
 * @final: 	21/06/2008
 * @param: 	megaman *, ponteiro para o megaman
 * @param: 	int, número da animação que irá mudar
 * @param: 	int, número do frame da animação que irá começar
 */
void megamanChangeAnimation(megaman *mega,int anim,int frame,int time)
{
	mega->animationPlaying=anim;
	mega->animationPack.animation[mega->animationPlaying].frameOn	= frame;
	mega->animationPack.animation[mega->animationPlaying].timeOn	= time;
}
/**
 * função que muda a animação atual do megaman apenas se a animacao não estiver passando
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	21/06/2008
 * @final: 	21/06/2008
 * @param: 	megaman *, ponteiro para o megaman
 * @param: 	int, número da animaçao para mudar
 * @param: 	int, número do frame que a animação deve começar
 */
void megamanChangAnimationIfChange(megaman *mega, int anim,int frame,int time)
{
	if(mega->animationPlaying!=anim)
		megamanChangeAnimation(mega,anim,frame,time);
}
/**
 * função que faz o megaman pular
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	21/06/2008
 * @final: 	25/06/2008
 * @param: 	megaman *, ponteiro para o megaman
 */
void megamanJump(megaman *mega)
{
	//toca som de pulo
	mega->y-=2;
	mega->yPulse=-2*mega->yPulseMax;
	megamanChangeAnimation(mega,animJump,0,0);
}
/**
 * função para saber se o megaman morreu
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	04/07/2008
 * @final: 	04/07/2008
 * @param: 	megaman *, ponteiro para o megaman
 * @return:	int
 */
int megamanIsDead(megaman *mega)
{
	if(
		mega->life<1
		|| mega->y>screen->h+20
	)
	{
		mega->life=0;
		return 1;
	}
	return 0;
}

/**
 * função para desenhar o megaman na tela
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	22/06/2008
 * @final: 	06/07/2008
 * @param: 	BITMAP *, ponteiro para a superfície
 * @param: 	megaman *, ponteiro para o megaman
 */
void megamanDraw(BITMAP *layer, megaman *mega,background *bg)
{
	if(mega->imortal==0 ||(mega->imortal>0 && mega->imortal%2))
		gorgonShowAnimation(layer,&mega->animationPack.animation[mega->animationPlaying],&mega->spritePack,mega->pal[mega->weapons.weaponInUse],mega->direction,mega->x+bg->bg.posX,mega->y+bg->bg.posY);
	if(debug)
	{
		int i;
		textout_ex(layer,font,"Debug:",10,180,makecol(255,255,0),-1);
		textprintf_ex(layer,font,10,190,makecol(255,255,0),-1,"posx: %.2f",mega->x);
		textprintf_ex(layer,font,10,200,makecol(255,255,0),-1,"posy: %.2f",mega->y);
		textprintf_ex(layer,font,10,210,makecol(255,255,0),-1,"life: %d",mega->life);
		textprintf_ex(layer,font,10,220,makecol(255,255,0),-1,"Weapon in use: %d",mega->weapons.weaponInUse);
		textprintf_ex(layer,font,10,230,makecol(255,255,0),-1,"Weapon bar: %d",mega->weapons.weapon[mega->weapons.weaponInUse].bar);
		
		textprintf_ex(layer,font,150,190,makecol(255,255,0),-1,"Control: %d",mega->control);
		textprintf_ex(layer,font,150,200,makecol(255,255,0),-1,"Animation: %d",mega->animationPlaying);
		textprintf_ex(layer,font,150,210,makecol(255,255,0),-1,"Direction: %d",mega->direction);
		textprintf_ex(layer,font,150,220,makecol(255,255,0),-1,"State: %s",(!backgroundCollision((int)mega->x-5,(int)mega->y-2, 10,2,bg)) ? "in Air" : "on Ground");
		gorgonDrawAnimationClsn(layer,&mega->animationPack.animation[mega->animationPlaying],bg->bg.posX+mega->x,bg->bg.posY+mega->y,mega->direction);
	}
}
/**
 * função para mover o megaman no eixoX
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	22/06/2008
 * @final: 	25/06/2008
 * @param: 	megaman *, ponteiro para o megaman
 * @param: 	background *, ponteiro para o cenário
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
 * @author:	Cantídio Oliveira Fontes
 * @since: 	22/06/2008
 * @final: 	25/06/2008
 * @param: 	megaman *, ponteiro para o megaman
 * @param: 	background *, ponteiro para o cenário
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
					megamanChangAnimationIfChange(mega,animArrive,0,0);
				else
				{
					megamanChangAnimationIfChange(mega,animStand,0,0);
					gorgonPlaySound(mega->sound[reachGround],&mega->audio,3);
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
		if(mega->control && mega->yPulse>0) megamanChangAnimationIfChange(mega,animFall,0,0);
	}
}
/**
 * função que faz o megaman entrar em estado de acerto
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	05/07/2008
 * @final:	05/07/2008
 * @param:	megaman *, ponteiro para o megaman
 * @param:	short, dano que o megaman recebeu
 * @param:	char, direção oriunda do dano
 * @param:	short, pulso que ele deslocará no eixo x
 */
void megamanHit(megaman *mega,short damage,char direction,short pulse)
{
	if(mega->imortal==0)
	{
		mega->control=0;
		mega->xPulse= (direction==NORMAL) ? pulse : -pulse;
		mega->life-=damage;
		mega->imortal=50;
		megamanChangAnimationIfChange(mega,animHit,0,0);
		gorgonPlaySound(mega->sound[soundHit],&mega->audio,3);
	}
}
/**
 * função para fazer o megaman atirar
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	22/06/2008
 * @final: 	03/07/2008
 * @param: 	megaman *, ponteiro para o megaman
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
			mega->lastShot	= 10;
			x		= mega->x;
			y		= mega->y-15;
			stand		= animShotStand;
			walk		= animShotWalking;
			inAir		= animShotInAir;
			break;
		case shadowBlade:
		case boomerang:
		case bombThower:
			mega->xPulse	= 0;
			mega->control	= 0;
			x		= mega->x;
			y		= mega->y-15;
			stand		= animThrowStand;
			walk		= animThrowStand;
			inAir		= animThrowInAir;
			break;
		
		case thunderShot:
//			mega->xPulse	= 0;
			x		= mega->x;
			y		= mega->y-5;
			stand		= animShotStand;
			walk		= animShotWalking;
			inAir		= animShotInAir;
			break;
	}
	switch(mega->animationPlaying)
	{
		case animStand:
			mega->control=0;
			megamanChangAnimationIfChange(mega,stand,0,0);
			weaponShot(&mega->weapons,x,y,mega->direction);
			break;
		case animWalk:
		case animShotWalking:
			megamanChangAnimationIfChange(mega,walk,mega->animationPack.animation[mega->animationPlaying].frameOn,mega->animationPack.animation[mega->animationPlaying].timeOn);
			weaponShot(&mega->weapons,x,y,mega->direction);
			break;
		case animJump: case animFall:
			mega->control=0;
			megamanChangAnimationIfChange(mega,inAir,0,0);
			weaponShot(&mega->weapons,x,y,mega->direction);
			break;
	}
}
/**
 * função que lida com os eventos de finalização de animações do megaman
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	20/06/2008
 * @final:	05/07/2008
 * @param:	megaman *, ponteiro para o megaman
 */
void megamanAnimationFinishedEvents(megaman *mega)
{
	if(gorgonAnimationFinished(&mega->animationPack.animation[mega->animationPlaying]))
		switch(mega->animationPlaying)
		{
			case animHit:
			case animArrive:
			case animShotStand:
			case animThrowStand:
			case animSlide:
				mega->control=1;
				megamanChangAnimationIfChange(mega,animStand,0,0);
				mega->xPulse=0;
				break;
			case animThrowInAir:
			case animShotInAir:
				mega->control=1;
				megamanChangAnimationIfChange(mega,animFall,0,0);
				break;
		}
}
/**
 * função que lida com os eventos de animações do megaman
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	20/06/2008
 * @final:	01/07/2008
 * @param:	megaman *, ponteiro para o megaman
 */
void megamanAnimationRunnigEvents(megaman *mega)
{
	switch(mega->animationPlaying)
	{
		case animSlide:
			if(mega->direction==NORMAL)
				mega->xPulse=mega->xPulseValue*4;
			else
				mega->xPulse=-mega->xPulseValue*4;
			break;
	}
}
/**
 * função que lida com os eventos básicos do megaman
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	18/06/2008
 * @final:	03/07/2008
 * @param:	megaman *, ponteiro para o megaman
 * @param:	background *, ponteiro para o cenário
 * @param:	gorgonAudio *, ponteiro para o sistema sonoro
 * @return:	int
 */
int megamanNormalEvents(megaman *mega,background *bg)
{
	if(mega->control)
	{
		if(key[mega->controlDef.jump] && key[mega->controlDef.down] && backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
		{
			mega->control=0;
			megamanChangAnimationIfChange(mega,animSlide,0,0);
		}
		else if(key[mega->controlDef.shot] && canShot(&mega->weapons))
		{
			gorgonPlaySound(mega->sound[soundShot],&mega->audio,3);
			megamanShot(mega);
		}
		else if(key[mega->controlDef.jump] && backgroundCollision((int)mega->x-5,(int)mega->y, 10,2,bg))
		{
				megamanJump(mega);
		}
		else if(key[mega->controlDef.right])
		{
			mega->direction=NORMAL;
			if(mega->lastShot==0 && backgroundCollision((int)mega->x-5,(int)mega->y-2, 10,2,bg))
			{
				if(mega->animationPlaying!=animShotWalking)
					megamanChangAnimationIfChange(mega,animWalk,0,0);
				else
					megamanChangAnimationIfChange(mega,animWalk,mega->animationPack.animation[mega->animationPlaying].frameOn,mega->animationPack.animation[mega->animationPlaying].timeOn);
			}
			if(mega->xPulse<mega->xPulseMax)
			{
				mega->xPulse+=mega->xPulseValue;
			}
		}
		else if(key[mega->controlDef.left])
		{
			mega->direction=H_FLIP;
			if(mega->lastShot==0 && backgroundCollision((int)mega->x-5,(int)mega->y-2, 10,2,bg))
			{
				if(mega->animationPlaying!=animShotWalking)
					megamanChangAnimationIfChange(mega,animWalk,0,0);
				else
					megamanChangAnimationIfChange(mega,animWalk,mega->animationPack.animation[mega->animationPlaying].frameOn,mega->animationPack.animation[mega->animationPlaying].timeOn);
			}
			if(mega->xPulse>-mega->xPulseMax)
			{
				mega->xPulse-=mega->xPulseValue;
			}
		}
		else if(!key[mega->controlDef.right] && mega->xPulse>0)
		{
			megamanChangAnimationIfChange(mega,animStand,0,0);
			mega->xPulse-=mega->xPulseValue;
			if(mega->xPulse<0) mega->xPulse=0;
		}
		else if(!key[mega->controlDef.left] && mega->xPulse<0)
		{
			megamanChangAnimationIfChange(mega,animStand,0,0);
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
	if(mega->lastShot>0) mega->lastShot--;
	if(mega->imortal>0) mega->imortal--;
	megamanAnimationFinishedEvents(mega);
	megamanAnimationRunnigEvents(mega);
	megamanMoveX(mega,bg);
	megamanMoveY(mega,bg);
}

