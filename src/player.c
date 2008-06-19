#include "../include/player.h"

/**
 * função para criar e setar todos os atributos do megaman
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 19/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @return: int
 */
int createMegaman(megaman *mega)
{
	if(mega!=NULL)
	{
		mega->life		= MaxHealth;
		mega->spritePack	= NULL;
		mega->animationPack	= NULL;
		mega->xPulse		= 0;
		mega->yPulse		= 0;
		mega->xPulseValue	= 1.5;
		mega->yPulseValue	= 1.5;
		mega->xPulseMax		= 6;
		mega->yPulseMax		= 6;
		mega->control		= 0;
		mega->direction		= 1;
		return createWeaponList(&mega->weapon);
	}
	return 0;
}
/**
 * função que lida com os eventos básicos do megaman
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 18/06/2008
 * @final: 19/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @return: int
 */
int normalEventsMegaman(megaman *mega)
{
	if(mega!=NULL)
	{
		if(mega->control)
		{
			if(key[ATIRA])
			{
			}
			else if(key[PULA])
			{
			}
			else if(key[FRENTE])
			{
			}
			else if(key[TRAZ])
			{
			}
			else if(key[ARMAF])
			{
				nextWeapon(&mega->weapon);
			}
			else if(key[ARMAB])
			{
				previousWeapon(&mega->weapon);
			}
		}


		return 1;
	}
	return 0;
}


#endif
