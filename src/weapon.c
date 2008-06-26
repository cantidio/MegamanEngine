#include "../include/weapon.h"

/**
 * função para criar uma lista de armas
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 19/06/2008
 * @param: weaponList *, ponteiro para a lista de armas que deseja-se criar/zerar
 * @return: int
 */
int createWeaponList(weaponList *list)
{
	int i;
	int j;
	if(list!=NULL)
	{
		gorgonLoadSpritePack(&list->spritePack,"resource/weapon.spk");
		gorgonLoadAnimationPack(&list->animationPack,"resource/weapon.apk");
		for(i=0; i<weaponNumber; i++)
		{
			list->weapon[i].ative	= 0;
			list->weapon[i].bar	= 0;
			list->weapon[i].cost	= 0;
		}
		list->weaponInUse=0;
		return 1;
	}
	return 0;
}
/**
 * função para setar os valores de um weapon
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 25/06/2008
 * @final: 25/06/2008
 * @param: weapons *, ponteiro para o weapon
 * @param: float, pulso horizontal
 * @param: float, pulso vertical
 * @param: short, número máximo de tiros possíveis
 * @return: int 1 se não houve erro ou 0 se ouve erro
 */
int createWeapon(weapons *weapon,short animationStand,short animationColide,short cost,float xPulse,float yPulse,float xPulseValue,float yPulseValue,short maxShots)
{
	int i;
	weapon->animationStand	= animationStand;
	weapon->animationColide	= animationColide;
	weapon->cost		= cost;
	weapon->xPulse		= xPulse;
	weapon->yPulse		= yPulse;
	weapon->xPulseValue	= xPulseValue;
	weapon->yPulseValue	= yPulseValue;
	weapon->maxShots	= maxShots;
	weapon->shot		= (shots *)malloc(sizeof(shots)*maxShots);
	if(weapon->shot!=NULL)
	{
		for(i=0; i<weapon->maxShots; weapon->shot[i].ative=0,i++);
		return 1;
	}
	return 0;
}
/**
 * função fazer criar todas as armas com suas devidas definições
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 25/06/2008
 * @final: 26/06/2008
 * @param: weaponList *, ponteiro para a lista de armas disponível
 */
int createAllWeapons(weaponList *list)
{
	if(list!=NULL)
	{
		createWeaponList(list);
		createWeapon(&list->weapon[plasmaShot],1,2,0,3.5,0,0,0,6);	//cria arma de plasma
		getNewWeapon(list,plasmaShot);					//ativa arma de plasma
		
		createWeapon(&list->weapon[boomerang],0,3,5,10,5,-0.5,-0.3,2);	//cria arma boomerang
		getNewWeapon(list,boomerang);					//ativa arma boomerang
	
		createWeapon(&list->weapon[bombThower],3,3,5,-10,0,0.5,-0.3,2);	//cria arma bomba
		getNewWeapon(list,bombThower);					//ativa arma bomba
	}
	return 0;
}
/**
 * função para desenhar os tiros das armas
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 25/06/2008
 * @final: 26/06/2008
 * @param: BITMAP *, ponteiro para a superfície para onde os tiros serão desenhados
 * @param: weaponList *, ponteiro para a lista de armas disponível
 * @param: background *, ponteiro para o cenário
 */
void weaponsDraw(BITMAP *layer,weaponList *list,background *bg)
{
	int i,j;
//	int x=-bg->bg.posX;
//	int y=-bg->bg.posY;
	for(i=0; i<weaponNumber; i++)
	{
		if(list->weapon[i].ative)				//se a arma estiver ativada
		{
			for(j=0; j<list->weapon[i].maxShots; j++)	
			{
				
				if(list->weapon[i].shot[j].ative)	//se o tiro estiver ativado(em uso)
				{

					gorgonShowAnimation(layer,&list->animationPack.animation[list->weapon[i].shot[j].animationPlaying],&list->spritePack,NULL,list->weapon[i].shot[j].direction,(int)list->weapon[i].shot[j].x,(int)list->weapon[i].shot[j].y);

				}
			}
		}
	}
}
/**
 * função fazer executar os eventos normais de todos os tiros
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 25/06/2008
 * @final: 26/06/2008
 * @param: weaponList *, ponteiro para a lista de armas disponível
 * @param: background *, ponteiro para o cenário
 */
void weaponsNormalEvents(weaponList *list,background *bg)
{
	int i,j;
	for(i=0; i<weaponNumber; i++)
	{
		if(list->weapon[i].ative)				//se a arma estiver ativada
		{
			for(j=0; j<list->weapon[i].maxShots; j++)	
			{
				if(list->weapon[i].shot[j].ative)	//se o tiro estiver ativado(em uso)
				{
					list->weapon[i].shot[j].xPulse+=list->weapon[i].xPulseValue;
					list->weapon[i].shot[j].yPulse+=list->weapon[i].yPulseValue;
					list->weapon[i].shot[j].x+=list->weapon[i].shot[j].xPulse;
					list->weapon[i].shot[j].y+=list->weapon[i].shot[j].yPulse;
					if(list->weapon[i].shot[j].x <-10 || list->weapon[i].shot[j].x>bg->bg.width+10 || list->weapon[i].shot[j].y <-10 || list->weapon[i].shot[j].y> bg->bg.height+10)
						list->weapon[i].shot[j].ative=0;
				}
			}
		}
	}
}
/**
 * função fazer uma arma atirar
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 25/06/2008
 * @final: 26/06/2008
 * @param: weaponList *, ponteiro para a lista de armas disponível
 * @param: float , posição inicial no eixo x
 * @param: float , posição inicial no eixo y
 * @param: char, direção do tiro
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
			if(direction==NORMAL)
			{
				list->weapon[list->weaponInUse].shot[i].xPulse	= list->weapon[list->weaponInUse].xPulse;
				list->weapon[list->weaponInUse].shot[i].yPulse	= list->weapon[list->weaponInUse].yPulse;
				list->weapon[list->weaponInUse].shot[i].x	= x;
				list->weapon[list->weaponInUse].shot[i].y	= y;
			}
			else
			{
				list->weapon[list->weaponInUse].shot[i].xPulse	= -list->weapon[list->weaponInUse].xPulse;
				list->weapon[list->weaponInUse].shot[i].yPulse	= -list->weapon[list->weaponInUse].yPulse;
				list->weapon[list->weaponInUse].shot[i].x	= -x;
				list->weapon[list->weaponInUse].shot[i].y	= -y;
			}
			
			break;
		}
	}
}
/**
 * função para validar uma nova arma
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 18/06/2008
 * @param: weaponList *, ponteiro para lista de armas
 * @param: int, a arma que deseja-se ativar
 * @return: int
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
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 26/06/2008
 * @param: weaponList *, ponteiro para a lista de armas que deseja-se que a ação seja executada
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
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 26/06/2008
 * @param: weaponList *, ponteiro para a lista de armas que deseja-se que a ação seja executada
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

