#include "../include/menu.h"

/**
 * função para mostrar o disclaimer hehe
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 25/06/2008
 * @final: 25/06/2008
 * @param: inputControl *, ponteiro para a estrutura de controles
 * @return: int 0 se deu erro ou 1 se ocorreu tudo bem
 */
int showLogos(inputControl *control)
{
	BITMAP 			*layer;
	gorgonSpritePack 	spritePack;
	gorgonAnimationPack	animationPack;
printf("slala\n");
	layer=create_bitmap(screen->w,screen->h);
printf("slala\n");
	printf("%d\n",gorgonLoadSpritePack(&spritePack,"./resource/intro.spk"));
printf("slala\n");
	gorgonLoadAnimationPack(&animationPack,"./resource/intro.apk");
	key[control->start]=0;
	timer=0;
printf("slala\n");
	while(!key[control->start] && !key[KEY_ESC])
	{
		if(timer>0)
		{
			clear(layer);
			textout_centre_ex(layer,font,"This is a test made with GorgonLib",		layer->w/2,40,makecol(230,230,230),-1);
			textout_centre_ex(layer,font,"This engine is free and open source",		layer->w/2,50,makecol(230,230,230),-1);
			textout_centre_ex(layer,font,"If you paid for this you were fooled",		layer->w/2,60,makecol(230,230,230),-1);
			textout_centre_ex(layer,font,"Any comment, sugestion or greetings:",		layer->w/2,70,makecol(230,230,230),-1);
			textout_centre_ex(layer,font,"aniquilatorbloody@gmail.com",			layer->w/2,80,makecol(230,230,230),-1);
			textout_centre_ex(layer,font,"Megaman is a trademark of",			layer->w/2,100,makecol(230,230,230),-1);
		
			gorgonShowAnimation(layer,&animationPack.animation[0],&spritePack,NULL,NORMAL,(layer->w-spritePack.sprite[0].image->w)/2,layer->h/2);
			if(gorgonAnimationFinished(&animationPack.animation[0])) key[control->start]=1;
			blit(layer,screen,0,0,0,0,layer->w,layer->h);
			timer--;
		}
	}
	destroy_bitmap(layer);
	gorgonDestroyAnimationPack(&animationPack);
	gorgonDestroySpritePack(&spritePack);
}
/**
 * função para imprimir o menu principal na tela
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 25/06/2008
 * @final: 25/06/2008
 * @param: inputControl *, ponteiro para a estrutura de controle
 * @return: int a opção escolhida no menu
 */
int mainMenu(inputControl *control,gorgonAudio *audio)
{
	gorgonSpritePack 	spritePack;
	gorgonSound		*change;
	gorgonSound		*choose;
	BITMAP 			*layer;
	int 			selected=0;


	gorgonLoadSpritePack(&spritePack,"./resource/intro.spk");
	gorgonLoadSound(&change,"./resource/sons/mmse003.wav",audio);
	gorgonLoadSound(&choose,"./resource/sons/mmse011.wav",audio);
	layer=create_bitmap(screen->w,screen->h);

	if(layer!=NULL)
	{
		timer=0;
		clear_keybuf();
		key[control->start]=0;
		while(!key[control->start])
		{
			while(timer>0)
			{
				clear(layer);
				if(key[control->up])
				{
					gorgonPlaySound(change,audio,3);
					if(selected>0) selected--;
					else selected=2;
					key[control->up]=0;
				}
				else if(key[control->down])
				{
					gorgonPlaySound(change,audio,3);
					if(selected<2) selected++;
					else selected=0;
					key[control->down]=0;
				}
				gorgonDrawSpriteByIndex(layer,&spritePack,NULL,7,NORMAL,(layer->w-spritePack.sprite[7].image->w)/2,70);
				gorgonDrawSpriteByIndex(layer,&spritePack,NULL,8,NORMAL,(layer->w-spritePack.sprite[8].image->w*2),120);
				textout_ex(layer,font,"Start Game",	110,130,makecol(230,230,230),-1);
				textout_ex(layer,font,"Options",	110,140,makecol(230,230,230),-1);
				textout_ex(layer,font,"Exit",		110,150,makecol(230,230,230),-1);
				textout_ex(layer,font,">",		103,130 + selected*10,makecol(230,230,230),-1);
				blit(layer,screen,0,0,0,0,layer->w,layer->h);
				timer--;
			}
		}
		gorgonPlaySound(choose,audio,3);
		rest(300);
		destroy_bitmap(layer);
		gorgonDestroySpritePack(&spritePack);
		gorgonDestroySound(change);
		gorgonDestroySound(choose);
		return selected;
	}
	printf("erro ao alocar memória\n");
	exit(1);
}
/**
 * função que exibe o menu para configuração das teclas usadas no jogo
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 25/06/2008
 * @final: 25/06/2008
 * @param: inputControl *, ponteiro para a estrutura de controles
 * @return: int 0 se ocorreu erro ou 1 se ocorreu tudo bem
 */
int optionMenu(inputControl *control)
{
	BITMAP *layer;
	int selected		= 0;
	
	key[control->start]=0;
	layer=create_bitmap(screen->w,screen->h);
	if(layer!=NULL)
	{
		timer=0;
		while(!(key[control->start] && selected==8))
		{
			while(timer>0)
			{
				if(key[control->up])
				{
					if(selected>0) selected--;
					else selected=8;
					key[control->up]=0;
				}
				else if(key[control->down])
				{
					if(selected<8) selected++;
					else selected=0;
					key[control->down]=0;
				}
				else if(key[control->start])
				{
					clear_keybuf();
					switch(selected)
					{
						case 0: ureadkey(&control->up);	break;
						case 1: ureadkey(&control->down);	break;
						case 2: ureadkey(&control->left);	break;
						case 3: ureadkey(&control->right);	break;
						case 4: ureadkey(&control->shot);	break;
						case 5: ureadkey(&control->jump);	break;
						case 6: ureadkey(&control->weaponF);	break;
						case 7: ureadkey(&control->weaponB);	break;
					}
					clear_keybuf();
				}
				clear(layer);
				textout_ex(layer,font,"Up",			50,70,makecol(230,230,230),-1);
				textout_ex(layer,font,"Down",			50,80,makecol(230,230,230),-1);
				textout_ex(layer,font,"Left",			50,90,makecol(230,230,230),-1);
				textout_ex(layer,font,"Right",			50,100,makecol(230,230,230),-1);
				textout_ex(layer,font,"Shot",			50,110,makecol(230,230,230),-1);
				textout_ex(layer,font,"Jump",			50,120,makecol(230,230,230),-1);
				textout_ex(layer,font,"Next Weapon",		50,130,makecol(230,230,230),-1);
				textout_ex(layer,font,"Previous Weapon",	50,140,makecol(230,230,230),-1);
				textout_ex(layer,font,"Exit",			50,150,makecol(230,230,230),-1);
	
				textprintf_ex(layer,font,240,70,makecol(230,230,230),-1,"%s",scancode_to_name(control->up));
				textprintf_ex(layer,font,240,80,makecol(230,230,230),-1,"%s",scancode_to_name(control->down));
				textprintf_ex(layer,font,240,90,makecol(230,230,230),-1,"%s",scancode_to_name(control->left));
				textprintf_ex(layer,font,240,100,makecol(230,230,230),-1,"%s",scancode_to_name(control->right));
				textprintf_ex(layer,font,240,110,makecol(230,230,230),-1,"%s",scancode_to_name(control->shot));
				textprintf_ex(layer,font,240,120,makecol(230,230,230),-1,"%s",scancode_to_name(control->jump));
				textprintf_ex(layer,font,240,130,makecol(230,230,230),-1,"%s",scancode_to_name(control->weaponF));
				textprintf_ex(layer,font,240,140,makecol(230,230,230),-1,"%s",scancode_to_name(control->weaponB));
		

				textout_ex(layer,font,">",		43,70 + selected*10,makecol(230,230,230),-1);
				blit(layer,screen,0,0,0,0,layer->w,layer->h);
				timer--;
			}
		}
		return 1;
	}
	printf("erro ao alocar memória\n");
	return 0;
}
