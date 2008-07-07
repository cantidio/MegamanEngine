#ifndef ENEMY_JACK
#define ENEMY_JACK
#include "../../gorgon_core/include/gorgon.h"
#include "weapon.h"
#include "background.h"
#include "player.h"

#define JACK_LIFE 	10
#define JACK_STAND	0
#define JACK_THROW	1
#define IRON_BALL	2
#define	EXPLOSION	3
#define IRON_BALL_X	5

typedef struct
{
	gorgonAnimationPack	animationPack;
	gorgonAudio		audio;
	gorgonSound		*shot;		//som do tiro
	gorgonSound		*hit;		//som de acerto
	gorgonSound		*die;		//som da morte
	shots 			ironBall;
	short 			animationPlaying;
	short			life;
	short			x;
	short			y;
	char 			imortal;
	char			direction;
	char			ative;
}enemyJack;

typedef struct
{
	gorgonSpritePack	spritePack;
	gorgonAudio		audio;
	gorgonSound		*shot;		//som do tiro
	gorgonSound		*hit;		//som de acerto
	gorgonSound		*die;		//som da morte
	enemyJack 		*jack;
	short			newEnemy;	//indice do proximo inimigo a adicionado
	short			enemyNumber;	//número de inimigos
}enemyJackPack;

int	createEnemyJack(enemyJackPack *jackPack,gorgonAudio *audio,short enemyNumber);
int	createJack(enemyJackPack *jackPack,short x,short y);
int	destroyJack(enemyJack *jack);
int	destroyEnemyJack(enemyJackPack *jackPack);
void	jackCheckAtivation(enemyJack *jack,megaman *mega, background *bg);
void	jackAnimationFinishedEvents(enemyJack *jack,megaman *mega);
int	jackColideMegaman(enemyJack *jack,megaman *mega);
int	weaponColideJack(enemyJack *jack, weapons *weapon);
int	jackCanBeHit(enemyJack *jack);
int	megamanWeaponColideJack(enemyJack *jack,megaman *mega);
void	jackNormalEvents(enemyJack *jack,background *bg,megaman *mega);
void	jackPackNormalEvents(enemyJackPack *jackPack,background *bg,megaman *mega);
void	jackDraw(BITMAP *layer,enemyJackPack *jackPack, background *bg);

#endif
