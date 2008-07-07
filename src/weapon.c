#include "../include/weapon.h"
/**
 * função para criar uma lista de armas
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	18/06/2008
 * @final: 	19/06/2008
 * @param: 	weaponList *, ponteiro para a lista de armas que deseja-se criar/zerar
 * @return:	int
 */
void createWeaponList(weaponList *list,gorgonAudio *audio)
{
	int i;
	int j;
	if(list!=NULL)
	{
		list->audio=*audio;
		gorgonLoadSound(&list->hitSound,"./resource/sons/mmse014.wav",&list->audio);
		gorgonLoadSpritePack(&list->spritePack,"resource/weapon.spk");
		for(i=0; i<weaponNumber; i++)
		{
			list->weapon[i].ative	= 0;
			list->weapon[i].bar	= 0;
			list->weapon[i].cost	= 0;
		}
		list->weaponInUse=0;
	}
}
/**
 * função para desalocar a memória gasta pela lista de armas
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 04/07/2008
 * @final: 04/07/2008
 * @param: weaponList *, ponteiro para a lista de armas
 */
void destroyWeaponList(weaponList *list)
{
	int i,k;
	if(list!=NULL)
	{
		gorgonDestroySpritePack(&list->spritePack);
		gorgonDestroySound(list->hitSound);
		for(i=0; i<weaponNumber; i++)
		{
			if(list->weapon[i].ative)
			{
				for(k=0; k<list->weapon[i].maxShots; gorgonDestroyAnimationPack(&list->weapon[i].shot[k].animationPack),k++);
				free(list->weapon[i].shot);
				list->weapon[i].maxShots= 0;
				list->weapon[i].ative	= 0;
			}
		}
	}
}
/**
 * função para setar os valores de um weapon
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	25/06/2008
 * @final: 	01/07/2008
 * @param: 	weapons *, ponteiro para o weapon
 * @param: 	float, pulso horizontal
 * @param: 	float, pulso vertical
 * @param: 	short, número máximo de tiros possíveis
 * @return:	int 1 se não houve erro ou 0 se ouve erro
 */
int createWeapon(weapons *weapon,short animationStand,short animationColide,short cost,short power,short delay,float xPulse,float yPulse,float xPulseValue,float yPulseValue,short maxShots)
{
	int i;
	weapon->animationStand	= animationStand;
	weapon->animationColide	= animationColide;
	weapon->cost		= cost;
	weapon->power		= power;
	weapon->delayValue	= delay;
	weapon->delay		= 0;
	weapon->xPulse		= xPulse;
	weapon->yPulse		= yPulse;
	weapon->xPulseValue	= xPulseValue;
	weapon->yPulseValue	= yPulseValue;
	weapon->maxShots	= maxShots;
	weapon->shot		= (shots *)malloc(sizeof(shots)*maxShots);
	if(weapon->shot!=NULL)
	{
		for(i=0; i<weapon->maxShots; weapon->shot[i].ative=0,gorgonLoadAnimationPack(&weapon->shot[i].animationPack,"resource/weapon.apk"),i++);
		return 1;
	}
	return 0;
}
/**
 * função fazer criar todas as armas com suas devidas definições
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	25/06/2008
 * @final: 	02/07/2008
 * @param: 	weaponList *, ponteiro para a lista de armas disponível
 */
int createAllWeapons(weaponList *list,gorgonAudio *audio)
{
	if(list!=NULL)
	{
		createWeaponList(list,audio);//talvez 12
		//					animN	animD	Gasto	power	delay	PulsoX	PulsoY	gastX	gastY	maxTiros ao mesmo tempo
		createWeapon(&list->weapon[plasmaShot],	1,	12,	0,	1,	10,	5.5,	0,	0,	0,	6);	//cria arma de plasma
		createWeapon(&list->weapon[boomerang],	0,	30,	5,	5,	10,	9,	0,	-0.3,	0,	1);	//cria arma boomerang
		createWeapon(&list->weapon[bombThower],	4,	27,	4,	6,	20,	5,	-7,	0,	0.5,	2);	//cria arma bomba
		createWeapon(&list->weapon[thunderShot],15,	29,	3,	3,	10,	4,	0,	0,	0,	3);	//cria arma thunderShot
		createWeapon(&list->weapon[iceBlast],	3,	31,	1,	2,	10,	6,	0,	0,	0,	3);	//cria arma iceBlast		
		createWeapon(&list->weapon[fireBlast],	7,	28,	2,	2,	10,	6,	0,	0,	0,	3);	//cria arma fireBlast
		createWeapon(&list->weapon[shadowBlade],26,	32,	2,	3,	10,	7,	0,	0,	0,	5);	//cria arma shadowBlade

		getNewWeapon(list,plasmaShot);						//ativa arma de plasma
		getNewWeapon(list,boomerang);						//ativa arma boomerang
		getNewWeapon(list,bombThower);						//ativa arma bomba
		getNewWeapon(list,thunderShot);						//ativa arma thunderShot
		getNewWeapon(list,iceBlast);						//ativa arma iceBlast		
		getNewWeapon(list,fireBlast);						//ativa arma fireBlast
		getNewWeapon(list,shadowBlade);						//ativa arma shadowBlade
		
	}
	return 0;
}
int canShot(weaponList *list)
{
	int i;
	if(!(list->weapon[list->weaponInUse].bar>=list->weapon[list->weaponInUse].cost)) 	return 0;
	if(list->weapon[list->weaponInUse].delay>0)						return 0;
	for(i=0; i<list->weapon[list->weaponInUse].maxShots; i++)
		if(!list->weapon[list->weaponInUse].shot[i].ative)
			return 1;
	return 0;
}
/**
 * função para desenhar os tiros das armas
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	25/06/2008
 * @final: 	26/06/2008
 * @param: 	BITMAP *, ponteiro para a superfície para onde os tiros serão desenhados
 * @param: 	weaponList *, ponteiro para a lista de armas disponível
 * @param: 	background *, ponteiro para o cenário
 */
void weaponsDraw(BITMAP *layer,weaponList *list,background *bg)
{
	int i,j;
	int x;
	for(i=0; i<weaponNumber; i++)
	{
		if(list->weapon[i].ative)				//se a arma estiver ativada
		{
			for(j=0; j<list->weapon[i].maxShots; j++)	
			{
				if(list->weapon[i].shot[j].ative)	//se o tiro estiver ativado(em uso)
				{
					gorgonShowAnimation(layer,&list->weapon[i].shot[j].animationPack.animation[list->weapon[i].shot[j].animationPlaying],&list->spritePack,NULL,list->weapon[i].shot[j].direction,(int)list->weapon[i].shot[j].x+bg->bg.posX,(int)list->weapon[i].shot[j].y);
					if(debug)
						gorgonDrawAnimationClsn(layer,&list->weapon[i].shot[j].animationPack.animation[list->weapon[i].shot[j].animationPlaying],bg->bg.posX+list->weapon[i].shot[j].x,bg->bg.posY+list->weapon[i].shot[j].y,list->weapon[i].shot[j].direction);
				}
			}
		}
	}
}
int weaponClsnBackground(weapons *weapon,background *bg,int k)
{
	int i;
	int colision=0;
	int animation	= weapon->shot[k].animationPlaying;
	int frameOn	= weapon->shot[k].animationPack.animation[animation].frameOn;
	
	for(i=0; i<weapon->shot[k].animationPack.animation[animation].frame[frameOn].clsnBlue.boxNumber; i++)
	{
		if(backgroundCollision(weapon->shot[k].x+weapon->shot[k].animationPack.animation[animation].frame[frameOn].clsnBlue.x1[i],weapon->shot[k].y + weapon->shot[k].animationPack.animation[animation].frame[frameOn].clsnBlue.y1[i],weapon->shot[k].animationPack.animation[animation].frame[frameOn].clsnBlue.x1[i] - weapon->shot[k].animationPack.animation[animation].frame[frameOn].clsnBlue.x2[i],weapon->shot[k].animationPack.animation[animation].frame[frameOn].clsnBlue.y1[i]-weapon->shot[k].animationPack.animation[animation].frame[frameOn].clsnBlue.y2[i],bg))
		{
	 		colision=1;
			weapon->shot[k].animationPlaying=weapon->animationColide;
		}
	}
	return colision;
}


/**
 * função para tratar as colisões das armas com o cenário
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	25/06/2008
 * @final: 	28/06/2008
 * @param: 	weaponList *, ponteiro para a lista de armas disponível
 * @param: 	background *, ponteiro para o cenário
 */
void weaponsBackgroundColision(weaponList *list,background *bg)
{
	int i,j,k;
	for(i=0; i<weaponNumber; i++)
	{
		if(list->weapon[i].ative)				//se a arma estiver ativada
		{
			for(j=0; j<list->weapon[i].maxShots; j++)	
			{
				if(list->weapon[i].shot[j].ative)	//se o tiro estiver ativado(em uso)
				{
					
					if(weaponClsnBackground(&list->weapon[i],bg,j))
						gorgonPlaySound(list->hitSound,&list->audio,3);
				}
			}
		}
	}
}

/**
 * função fazer executar os eventos normais de todos os tiros
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	25/06/2008
 * @final: 	03/07/2008
 * @param: 	weaponList *, ponteiro para a lista de armas disponível
 * @param: 	background *, ponteiro para o cenário
 */
void weaponsNormalEvents(weaponList *list,background *bg)
{
	int i,j;
	for(i=0; i<weaponNumber; i++)
	{
		if(list->weapon[i].ative)					//se a arma estiver ativada
		{
			if(list->weapon[i].delay>0) list->weapon[i].delay--;	//delay entre um tiro e outro
			for(j=0; j<list->weapon[i].maxShots; j++)	
			{
				if(list->weapon[i].shot[j].ative)		//se o tiro estiver ativado(em uso)
				{
					if(list->weapon[i].shot[j].animationPlaying!=list->weapon[i].animationColide)
					{
						if(list->weapon[i].shot[j].direction==NORMAL)
						{
							list->weapon[i].shot[j].xPulse	+=list->weapon[i].xPulseValue;
							list->weapon[i].shot[j].yPulse	+=list->weapon[i].yPulseValue;
						}
						else
						{
							list->weapon[i].shot[j].xPulse	-=list->weapon[i].xPulseValue;
							list->weapon[i].shot[j].yPulse	+=list->weapon[i].yPulseValue;
						}
						list->weapon[i].shot[j].x		+=list->weapon[i].shot[j].xPulse;
						list->weapon[i].shot[j].y		+=list->weapon[i].shot[j].yPulse;
					
						if(list->weapon[i].shot[j].x <-10 || list->weapon[i].shot[j].x>bg->bg.width+10 || list->weapon[i].shot[j].y <-10 || list->weapon[i].shot[j].y> bg->bg.height+10)
							list->weapon[i].shot[j].ative=0;
					}
					else if(gorgonAnimationFinished(&list->weapon[i].shot[j].animationPack.animation[list->weapon[i].animationColide]))
						list->weapon[i].shot[j].ative=0;
				}
			}
		}
	}
	weaponsBackgroundColision(list,bg);
}
/**
 * função fazer uma arma atirar
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	25/06/2008
 * @final: 	02/07/2008
 * @param: 	weaponList *, ponteiro para a lista de armas disponível
 * @param: 	float , posição inicial no eixo x
 * @param: 	float , posição inicial no eixo y
 * @param: 	char, direção do tiro
 */
void weaponShot(weaponList *list,float x,float y,char direction)
{
	int i;
	for(i=0; i<list->weapon[list->weaponInUse].maxShots; i++)
	{
		if(!list->weapon[list->weaponInUse].shot[i].ative && list->weapon[list->weaponInUse].bar>=list->weapon[list->weaponInUse].cost)
		{
			list->weapon[list->weaponInUse].bar			-=list->weapon[list->weaponInUse].cost;
			list->weapon[list->weaponInUse].shot[i].ative		= 1;
			list->weapon[list->weaponInUse].shot[i].direction	= direction;
			list->weapon[list->weaponInUse].shot[i].animationPlaying= list->weapon[list->weaponInUse].animationStand;
			list->weapon[list->weaponInUse].delay			= list->weapon[list->weaponInUse].delayValue;
			if(direction==NORMAL)
			{
				list->weapon[list->weaponInUse].shot[i].xPulse	= list->weapon[list->weaponInUse].xPulse;
				list->weapon[list->weaponInUse].shot[i].yPulse	= list->weapon[list->weaponInUse].yPulse;
				list->weapon[list->weaponInUse].shot[i].x	= x+5;
				list->weapon[list->weaponInUse].shot[i].y	= y;
			}
			else
			{
				list->weapon[list->weaponInUse].shot[i].xPulse	= -(list->weapon[list->weaponInUse].xPulse);
				list->weapon[list->weaponInUse].shot[i].yPulse	= list->weapon[list->weaponInUse].yPulse;
				list->weapon[list->weaponInUse].shot[i].x	= x-5;
				list->weapon[list->weaponInUse].shot[i].y	= y;
			}
			break;
		}
	}
}
/**
 * função para validar uma nova arma
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since: 	18/06/2008
 * @final: 	18/06/2008
 * @param: 	weaponList *, ponteiro para lista de armas
 * @param: 	int, a arma que deseja-se ativar
 * @return:	int
 */
int getNewWeapon(weaponList *list, int weapon)
{
	if(list!=NULL)
	{
		list->weapon[weapon].ative	= 1;
		list->weapon[weapon].bar	= maxWeaponBar;
		return 1;
	}
	return 0;
}
/**
 * função para selecionar a primeira arma ativa depois da atual, se chegar ao fim da lista volta procurando do inicio
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	18/06/2008
 * @final: 	26/06/2008
 * @param: 	weaponList *, ponteiro para a lista de armas que deseja-se que a ação seja executada
 * @return:	int
 */
int nextWeapon(weaponList *list)
{
	int i;
	int backup;
	for(backup=list->weaponInUse,i=backup+1; i<weaponNumber; i++)
		if(list->weapon[i].ative)
		{
			list->weaponInUse=i;
			break;
		}
	if(list->weaponInUse==backup)
		for(i=0; i<weaponNumber; i++)
			if(list->weapon[i].ative)
			{
				list->weaponInUse=i;
				break;
			}
}
/**
 * função para selecionar a primeira arma ativa antes da atual, se chegar ao inicio da lista volta procurando do fim
 *
 * @author:	Cantídio Oliveira Fontes
 * @since: 	18/06/2008
 * @final: 	26/06/2008
 * @param: 	weaponList *, ponteiro para a lista de armas que deseja-se que a ação seja executada
 * @return:	int
 */
int previousWeapon(weaponList *list)
{
	int i;
	int backup;
	for(backup=list->weaponInUse, i=backup-1; i>=0; i--)
		if(list->weapon[i].ative)
		{
			list->weaponInUse=i;
			break;
		}
	if(list->weaponInUse==backup)
		for(i=weaponNumber-1; i>=0; i--)
			if(list->weapon[i].ative)
			{
				list->weaponInUse=i;
				break;
			}
}

