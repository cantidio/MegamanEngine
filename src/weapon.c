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
		for(i=0; i<weaponNumber; i++)
		{
			list->weapon[i].ative	= 0;
			list->weapon[i].bar	= 0;
			for(j=0; j<maxShots; list->weapon[i].shot[j].ative=0,j++);
		}
		list->weapon[plasmaShot].ative=1;
		return 1;
	}
	return 0;
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
 * @final: 19/06/2008
 * @param: weaponList *, ponteiro para a lista de armas que deseja-se que a ação seja executada
 */
int nextWeapon(weaponList *list)
{
	int i;
	int backup;
	for(i=backup=list->weaponInUse; i<weaponNumber; i++)
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
 * @final: 19/06/2008
 * @param: weaponList *, ponteiro para a lista de armas que deseja-se que a ação seja executada
 */
int previousWeapon(weaponList *list)
{
	int i;
	int backup;
	for(i=backup=list->weaponInUse; i>=0; i--)
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

