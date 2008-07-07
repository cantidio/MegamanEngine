#include "../include/enemy_jack.h"

/**
 * função que cria uma lista de inimigos Jack
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	04/07/2008
 * @param:	enemyJackPack *, ponteiro para a lista de inimigos
 * @param:	short, número de inimigos máximos possíveis
 * @return:	int
 */
int createEnemyJack(enemyJackPack *jackPack,gorgonAudio *audio,short enemyNumber)
{
	int i;
	if(enemyNumber>0)
	{
		jackPack->audio=*audio;
		gorgonLoadSound(&jackPack->shot,"./resource/sons/mmse013.wav",&jackPack->audio);
		gorgonLoadSound(&jackPack->hit,"./resource/sons/mmse032.wav",&jackPack->audio);
		gorgonLoadSound(&jackPack->die,"./resource/sons/mmse028.wav",&jackPack->audio);
		gorgonLoadSpritePack(&jackPack->spritePack,"./resource/enemy/jack.spk");
		jackPack->jack		= (enemyJack *)malloc(sizeof(enemyJack)*enemyNumber);
		jackPack->enemyNumber	= enemyNumber;
		jackPack->newEnemy=0;
		if(jackPack->jack!=NULL)
			for(i=0; i<enemyNumber; jackPack->jack[i].ative=0,jackPack->jack[i].ironBall.ative=0,i++);
		return 1;
	}
	return 0;
}
/**
 * função que cria/instancia um inimigo Jack
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	04/07/2008
 * @param:	enemyJack *, ponteiro para o inimigo
 * @param:	short, posição no eixo X que será criado
 * @param:	short, posição no exito Y que será criado
 * @param:	char, direção inicial
 */
int createJack(enemyJackPack *jackPack,short x,short y)
{
	int error;
	if(jackPack!=NULL)
	{
		if(gorgonLoadAnimationPack(&jackPack->jack[jackPack->newEnemy].animationPack,"./resource/enemy/jack.apk")!=GORGON_OK)		return 0;
		if(gorgonLoadAnimationPack(&jackPack->jack[jackPack->newEnemy].ironBall.animationPack,"./resource/enemy/jack.apk")!=GORGON_OK)	return 0;
		jackPack->jack[jackPack->newEnemy].audio			= jackPack->audio;
		jackPack->jack[jackPack->newEnemy].hit				= jackPack->hit;
		jackPack->jack[jackPack->newEnemy].die				= jackPack->die;
		jackPack->jack[jackPack->newEnemy].shot				= jackPack->shot;
		jackPack->jack[jackPack->newEnemy].ironBall.animationPlaying	= IRON_BALL;
		jackPack->jack[jackPack->newEnemy].ironBall.ative		= 0;
		jackPack->jack[jackPack->newEnemy].x				= x;
		jackPack->jack[jackPack->newEnemy].y				= y;
		jackPack->jack[jackPack->newEnemy].ative			= 1;
		jackPack->jack[jackPack->newEnemy].life				= JACK_LIFE;
		jackPack->jack[jackPack->newEnemy].animationPlaying		= JACK_STAND;
		jackPack->jack[jackPack->newEnemy].imortal			= 0;
		jackPack->jack[jackPack->newEnemy].direction			= NORMAL;
		jackPack->newEnemy++;
		return 1;
	}
	return 0;
}
/**
 * função para destruir um inimigo jack
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	06/07/2008
 * @param:	enemyJack *, ponteiro para o jack
 * @return:	int
 */
int destroyJack(enemyJack *jack)
{
	if(gorgonDestroyAnimationPack(&jack->animationPack)!=GORGON_OK)		return 0;
	if(gorgonDestroyAnimationPack(&jack->ironBall.animationPack)!=GORGON_OK)	return 0;
	return 1;
}
/**
 * função para destruir todos os inimigos jacks
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	06/07/2008
 * @param:	enemyJackPack *, ponteiro para o pacote de inimigos jack
 * @return:	int
 */
int destroyEnemyJack(enemyJackPack *jackPack)
{
	int i;
	if(gorgonDestroySound(jackPack->die)!=GORGON_OK)				return 0;
	if(gorgonDestroySound(jackPack->hit)!=GORGON_OK)				return 0;
	if(gorgonDestroySound(jackPack->shot)!=GORGON_OK)				return 0;
	if(gorgonDestroySpritePack(&jackPack->spritePack)!=GORGON_OK)			return 0;
	for(i=0; i<jackPack->enemyNumber; i++)
		if(!destroyJack(&jackPack->jack[i]))					return 0;
	free(jackPack->jack);
	jackPack->enemyNumber=0;
}
/**
 * função que checa se o inimigo jack está apto a ser ativado ou não
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	06/07/2008
 * @param:	enemyJack *, ponteiro para o inimigo
 * @param:	background *, ponteiro para o cenário
 */
void jackCheckAtivation(enemyJack *jack,megaman *mega, background *bg)
{
	if(jack->life>0 && (bg->bg.posX + jack->x)>=-10 && (bg->bg.posX + jack->x)<=330)
	{
		jack->ative = 1;
		if(mega->x > jack->x)
			jack->direction=NORMAL;
		else	jack->direction=H_FLIP;
	}
	else if((bg->bg.posX + jack->x)<=-30 || (bg->bg.posX + jack->x)>=350)
	{
		jack->ative		= 0;
		jack->life		= JACK_LIFE;
		jack->animationPlaying	= JACK_STAND;
		jack->imortal		= 0;
	}
}
/**
 * função que lida com os eventos relacionados com o térmido de alguma animação do inimigo Jack
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	04/07/2008
 * @param:	enemyJack *, ponteiro para o inimigo
 */
void jackAnimationFinishedEvents(enemyJack *jack,megaman *mega)
{
	if(jack->ative)
	{
		if(gorgonAnimationFinished(&jack->animationPack.animation[jack->animationPlaying]))
		{
			jack->animationPack.animation[jack->animationPlaying].frameOn	= 0;
			jack->animationPack.animation[jack->animationPlaying].timeOn	= 0;
			switch(jack->animationPlaying)
			{
				case JACK_STAND:
					if(!jack->ironBall.ative)
					{
						gorgonPlaySound(jack->shot,&jack->audio,3);
						jack->animationPlaying	= JACK_THROW;
						jack->ironBall.ative	= 1;
						jack->ironBall.direction= jack->direction;
						jack->ironBall.xPulse	= IRON_BALL_X;
						jack->ironBall.yPulse	= 0;
						jack->ironBall.y	= jack->y-10;
						if(jack->direction==NORMAL)
							jack->ironBall.x= jack->x+5;
						else	jack->ironBall.x= jack->x-5;
					}
					
					break;
				case JACK_THROW:
					jack->animationPlaying = JACK_STAND;
					if(mega->x > jack->x)
						jack->direction=NORMAL;
					else	jack->direction=H_FLIP;

					break;
				case EXPLOSION:
					jack->ative=0;
					break;
			}
		}
	}
}
/**
 * função para testar se o megaman colidiu com o jack
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	05/07/2008
 * @param:	enemyJack *, ponteiro para o jack
 * @param:	megaman *, ponteiro para o megaman
 * @return:	int
 */
int jackColideMegaman(enemyJack *jack,megaman *mega)
{
	if(jack->ative && gorgonAnimationClsn(&jack->animationPack.animation[jack->animationPlaying],jack->x,jack->y,CLSN_RED,jack->direction,&mega->animationPack.animation[mega->animationPlaying],mega->x,mega->y,CLSN_BLUE,mega->direction))
	{
		megamanHit(mega,7,jack->direction,5);
		return 1;
	}
	if(jack->ironBall.ative && gorgonAnimationClsn(&mega->animationPack.animation[mega->animationPlaying],mega->x,mega->y,CLSN_BLUE,mega->direction,&jack->animationPack.animation[jack->ironBall.animationPlaying],jack->ironBall.x,jack->ironBall.y,CLSN_RED,jack->ironBall.direction))
	{
		megamanHit(mega,7,jack->ironBall.direction,10);
		return 1;
	}
	return 0;
}
/**
 * função para testar se uma arma do megaman colidiu com o jack
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since:	05/07/2008
 * @final:	05/07/2008
 * @param:	enemyJack *, ponteiro para o jack
 * @param:	weapons *, ponteiro para a arma
 * @return:	int
 */
int weaponColideJack(enemyJack *jack, weapons *weapon)
{

	int k;
	int animation;
	int frameOn;
	
	for(k=0; k<weapon->maxShots; k++)
	{
		if(weapon->shot[k].ative)
		{
			animation	= weapon->shot[k].animationPlaying;
			frameOn		= weapon->shot[k].animationPack.animation[animation].frameOn;
			if(gorgonAnimationClsn(&jack->animationPack.animation[jack->animationPlaying],jack->x,jack->y,CLSN_BLUE,jack->direction,&weapon->shot[k].animationPack.animation[animation],weapon->shot[k].x,weapon->shot[k].y,CLSN_RED,weapon->shot[k].direction))
			{
				return 1;
			}
		}
	}
	return 0;
}
/**
 * função para saber se o jack pode ser acertado ou não
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since:	05/07/2008
 * @final:	05/07/2008
 * @param:	enemyJack *, ponteiro para o jack
 * @return:	int
 */

int jackCanBeHit(enemyJack *jack)
{
	if((jack->animationPlaying==JACK_STAND && jack->animationPack.animation[JACK_STAND].frameOn>15) || jack->animationPlaying==JACK_THROW)
		return 1;
	return 0;
}
/**
 * função para testar se alguma arma do megaman colidiu com o jack
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	05/07/2008
 * @param:	enemyJack *, ponteiro para o jack
 * @param:	megaman *, ponteiro para o megaman
 * @return:	int
 */
int megamanWeaponColideJack(enemyJack *jack,megaman *mega)
{
	int i;
	int width;
	int height;
	gorgonAnimation *anim;
	int animPlaying;
	if(jack->ative && jackCanBeHit(jack) && jack->imortal==0)
	{
		for(i=0; i<weaponNumber; i++)
			if(mega->weapons.weapon[i].ative && weaponColideJack(jack,&mega->weapons.weapon[i]))
			{
				gorgonPlaySound(jack->hit,&jack->audio,3);
				jack->life	-=mega->weapons.weapon[i].power;
				if(jack->life>0) jack->imortal	= 50;
				return 1;
			}
	}
	return 0;
}
/**
 * função que lida com os eventos básicos do inimigo Jack
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	04/07/2008
 * @param:	enemyJack *, ponteiro para o inimigo
 * @param:	background *, ponteiro para o cenário
 */
void jackNormalEvents(enemyJack *jack,background *bg,megaman *mega)
{
	jackCheckAtivation(jack,mega,bg);
	if(jack->ative)
	{
		jackAnimationFinishedEvents(jack,mega);
		jackColideMegaman(jack,mega);
		megamanWeaponColideJack(jack,mega);
		if(jack->imortal>0) jack->imortal--;
		if(jack->life<=0 && jack->animationPlaying!=EXPLOSION)	//se o life dele acabar
		{
			gorgonPlaySound(jack->die,&jack->audio,3);
			jack->animationPack.animation[jack->animationPlaying].frameOn	= 0;
			jack->animationPack.animation[jack->animationPlaying].timeOn	= 0;
			jack->animationPlaying						= EXPLOSION;
		}
	}
	if(jack->ironBall.ative)//se a bola estiver ativa
	{
		jack->ironBall.x+=(jack->ironBall.direction==NORMAL) ? jack->ironBall.xPulse : -jack->ironBall.xPulse;
		if((jack->ironBall.x + bg->bg.posX)<=-30 || (jack->ironBall.x + bg->bg.posX)>=350)
			jack->ironBall.ative=0;
	}
}
/**
 * função para coordenar os eventos principais dos inimigos Jacks
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	04/07/2008
 * @param:	enemyJackPack *, ponteiro para o pacote de jacks
 * @param:	background *, ponteiro para o cenário
 */
void jackPackNormalEvents(enemyJackPack *jackPack,background *bg,megaman *mega)
{
	int i;
	for(i=0; i<jackPack->enemyNumber; jackNormalEvents(&jackPack->jack[i],bg,mega),i++);
}
/**
 * função para desenhar os inimigos jack
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	04/07/2008
 * @param:	BITMAP *, ponteiro para a superfície a desenhar os inimigos
 * @param:	enemyJackPack *, ponteiro para o pacote de jacks
 * @param:	background *, ponteiro para o cenário
 */
void jackDraw(BITMAP *layer,enemyJackPack *jackPack, background *bg)
{
	int i,j;
	for(i=0; i<jackPack->enemyNumber; i++)
	{
		if(jackPack->jack[i].ative && (jackPack->jack[i].animationPlaying==EXPLOSION || (jackPack->jack[i].imortal==0 || (jackPack->jack[i].imortal%2))))
		{
		
			gorgonShowAnimation
			(
				layer,
				&jackPack->jack[i].animationPack.animation[jackPack->jack[i].animationPlaying],
				&jackPack->spritePack,
				NULL,
				jackPack->jack[i].direction,
				jackPack->jack[i].x+bg->bg.posX,
				jackPack->jack[i].y+bg->bg.posY
			);
			if(debug)
				gorgonDrawAnimationClsn(layer,&jackPack->jack[i].animationPack.animation[jackPack->jack[i].animationPlaying],bg->bg.posX +jackPack->jack[i].x,bg->bg.posY + jackPack->jack[i].y,jackPack->jack[i].direction);
		}
		if(jackPack->jack[i].ironBall.ative)
		{
			gorgonShowAnimation
			(
				layer,
				&jackPack->jack[i].ironBall.animationPack.animation[jackPack->jack[i].ironBall.animationPlaying],
				&jackPack->spritePack,
				NULL,
				jackPack->jack[i].ironBall.direction,
				jackPack->jack[i].ironBall.x+bg->bg.posX,
				jackPack->jack[i].ironBall.y+bg->bg.posY
			);
			if(debug)
				gorgonDrawAnimationClsn(layer,&jackPack->jack[i].ironBall.animationPack.animation[jackPack->jack[i].ironBall.animationPlaying],bg->bg.posX +jackPack->jack[i].ironBall.x,bg->bg.posY + jackPack->jack[i].ironBall.y,jackPack->jack[i].ironBall.direction);
		}
	}
}
