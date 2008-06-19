#ifndef WEAPON

#define WEAPON
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
#define	sparkShot		13
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
#define	naxShots		6
#define maxWeaponBar		100

typedef struct
{
	char ative;
	float	x;
	float	y;
}shots;

typedef struct
{
	char 	ative;
	short 	bar;
	shots	shot[maxShots];
}weapons;

typedef struct
{
	int 	weaponInUse;	//arma usada no momento
	weapons	weapon[weaponNumber];
}weaponList;

int createWeaponList(weaponList *list);
int getNewWeapon(weaponList *list, int weapon);
int nextWeapon(weaponList *list);
int previousWeapon(weaponList *list);
#endif
