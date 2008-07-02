#ifndef PLAYER

#define PLAYER
#include "../../gorgon_core/include/gorgon.h"
#include "./weapon.h"
#include "./background.h"
#include "./control.h"
#define MaxHealth 100
#define animStand		0
#define animWalk		1
#define animJump		2
#define animFall		3
#define animClimb		4
#define animClimbEnd		5
#define animShotStand		6
#define animShotWalking		7
#define animShotInAir		8
#define animShotInLadder	9
#define animTeleport		10
#define animArrive		11
#define animSlide		12
#define animTwist		13
#define animThrowStand		18
#define animThrowInAir		19
#define reachGround		0
#define	soundShot		1
typedef struct
{
	int 			life;
	int 			animationPlaying;
	short			lastShot;
	gorgonSpritePack 	spritePack;
	gorgonAnimationPack 	animationPack;
	gorgonSound 		**sound;
	RGB 			**pal;
	weaponList		weapons;
	float 			x;//posição no cenário
	float 			y;//posição no cenário
	float			xPulse;
	float			yPulse;
	float			xPulseValue;
	float			yPulseValue;
	float			xPulseMax;
	float			yPulseMax;
	char			imortal;//se o megaman esta imortal
	char 			control;//se o cara tem controle ou n
	inputControl		controlDef;
	char			direction;//direcao
}megaman;

int createMegaman(megaman *mega,inputControl *control,gorgonAudio *audio);
int destroyMegaman(megaman *mega);
void megamanChangeAnimation(megaman *mega,int anim,int frame,int time);
void megamanChangAnimationIfChange(megaman *mega, int anim,int frame,int time);
void megamanJump(megaman *mega);
void megamanDraw(BITMAP *layer, megaman *mega,background *bg);
int megamanNormalEvents(megaman *mega,background *bg,gorgonAudio *audio);

#endif
