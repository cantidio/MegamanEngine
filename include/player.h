#ifndef PLAYER

#define PLAYER
#include "../../gorgon_core/include/gorgon.h"
#include "./weapon.h"
#include "./background.h"
#include "./control.h"
#define MaxHealth 100

#define animTeleport	0
#define animArrive	1
#define animStand	2
#define animWalk	3
#define animJump	4
#define animFall	5
#define animShotStand	6
#define animShotInAir	7
#define animSlide	8

typedef struct
{
	int 			life;
	int 			animationPlaying;
	gorgonSpritePack 	spritePack;
	gorgonAnimationPack 	animationPack;
	RGB 			*pal;
	weaponList		weapons;
	float 			x;
	float 			y;
	float			xPulse;
	float			yPulse;
	float			xPulseValue;
	float			yPulseValue;
	float			xPulseMax;
	float			yPulseMax;
	char			imortal;//se o megaman esta imortal
	char 			control;//se o cara tem controle ou n
	char			direction;//direcao
}megaman;

int createMegaman(megaman *mega);
int unloadMegaman(megaman *mega);
void megamanChangeAnimation(megaman *mega,int anim);
void megamanChangAnimationIfChange(megaman *mega, int anim);
void megamanJump(megaman *mega);
void megamanDraw(BITMAP *layer, megaman *mega);
int megamanNormalEvents(megaman *mega,background *bg);

#endif
