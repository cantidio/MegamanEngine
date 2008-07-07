#ifndef WEAPON
#define WEAPON
#include <stdio.h>
#include "../../gorgon_core/include/gorgon.h"
#include "background.h"
#include "debug.h"
//megaman 1
#define	plasmaShot		0
#define	boomerang		1
#define	rockThower		2
#define	iceBlast		3
#define	bombThower		4
#define fireBlast		5
#define	thunderShot		6
#define	spiralShot		7
#define	weel			8
//megaman 2
#define	hurricane		9
#define	bubble			10
#define	flashShot		11
#define	grabBomb		12
#define	sparrkShot		13
#define	flameThower		14
#define	leafShield		15
#define	plataformer		16
//megaman 3
#define	needleCannon		17
#define	magnetMissile		18
#define	geminiLaser		19
#define	hardKnuckle		20
#define	spin			21
#define	searchSnake		22
#define	sparkShot		23
#define	shadowBlade		24

#define weaponNumber		25
#define maxWeaponBar		100

typedef struct
{
	gorgonAnimationPack	animationPack;		//pacote de animações
	char 			ative;			//se o tiro está ativo
	char			direction;		//direção do tiro
	short			animationPlaying;	//animação que está tocando no momento
	float			xPulse;			//velocidade no eixo x que o tiro está no momento
	float			yPulse;			//velocidade no eixo y que o tiro está no momento
	float			x;			//posição atual no eixo x do tiro
	float			y;			//posição atual no eixo y do tiro
}shots;

typedef struct
{
	char 	ative;					//se a arma está ativa
	short	animationStand;				//animação normal
	short	animationColide;			//animação quando colide ou destroi
	short	power;					//poder de ataque da arma
	short	cost;					//o custo para cada tiro da arma
	short 	bar;					//a barra de munição atual
	float	xPulse;					//velocidade no eixo x que o tiro está no momento
	float	yPulse;					//velocidade no eixo y que o tiro está no momento
	float	xPulseValue;				//velocidade que é acrescida ao tiro no eixo x
	float	yPulseValue;				//velocidade que é acrescida ao tiro no eixo y
	short 	maxShots;				//número máximo de tiros executados ao mesmo tempo
	shots	*shot;					//os tiros
	short	delay;					//tempo entre um tiro e outro
	short	delayValue;				//tempo entre um tiro e outro
}weapons;

typedef struct
{
	gorgonSpritePack	spritePack;		//pacote de sprites
	gorgonAudio		audio;			//salva as informações do audio
	gorgonSound		*hitSound;		//som que toca quando o tiro colide com
	int 			weaponInUse;		//arma usada no momento
	weapons			weapon[weaponNumber];	//as armas
	
}weaponList;

void 	createWeaponList(weaponList *list,gorgonAudio *audio);
void	destroyWeaponList(weaponList *list);
int 	createWeapon(weapons *weapon,short animationStand,short animationColide,short cost,short power,short delay,float xPulse,float yPulse,float xPulseValue,float yPulseValue,short maxShots);
int 	createAllWeapons(weaponList *list,gorgonAudio *audio);
int 	canShot(weaponList *list);
void 	weaponsDraw(BITMAP *layer,weaponList *list,background *bg);
void 	weaponsNormalEvents(weaponList *list,background *bg);
void 	weaponShot(weaponList *list,float x,float y,char direction);
int 	getNewWeapon(weaponList *list, int weapon);
int 	nextWeapon(weaponList *list);
int 	previousWeapon(weaponList *list);
#endif
