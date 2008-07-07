#include "../include/menu.h"
/**
 * função para tirar um shot da tela
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since: 	22/06/2008
 * @final:	22/06/2008
 */
void takeShot()
{
	PALETTE pal;
	long size=1;
	char nome[255];
	int i;
	for(i=0; size!=0; i++)
	{
		sprintf(nome,"./shots/shot_%.3d.bmp",i);
		size=file_size(nome);
	}
	printf("%s\n",nome);
	get_palette(pal);
	save_bmp(nome,screen,pal);
}
/**
 * função para aguardar um determinado tempo
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	25/06/2008
 * @final:	25/06/2008
 * @param:	short, modificador temporal
 */
void wait(short x)
{
	short tick	= 0;
	short seg	= 0;

	while(seg<x)
	{
		while(timer>0)
		{
			tick++;
			timer--;
			if(tick==30)
			{
				tick=0;
				seg++;
			}
		}
	}
}
/**
 * função para mostrar o disclaimer
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since: 	25/06/2008
 * @final: 	03/07/2008
 * @param: 	inputControl *, ponteiro para a estrutura de controles
 * @return: 	int 0 se deu erro ou 1 se ocorreu tudo bem
 */
int showLogos(inputControl *control)
{
	BITMAP 			*layer;
	gorgonSpritePack 	spritePack;
	gorgonAnimationPack	animationPack;
	FONT			*megaFont;
	
	gorgonLoadSpritePack(&spritePack,"./resource/intro.spk");
	gorgonLoadAnimationPack(&animationPack,"./resource/intro.apk");
	
	megaFont		= load_bitmap_font("./resource/font.pcx",NULL,NULL);
	layer			= create_bitmap(screen->w,screen->h);
	key[control->start]	= 0;
	timer			= 0;
	while(!key[control->start] && !key[KEY_ESC])
	{
		if(timer>0)
		{
			if(key[KEY_F10])
			{
				takeShot();
				key[KEY_F10]=0;
			}
			clear(layer);
			textout_centre_ex(layer,megaFont,"This is a test made with GorgonLib",		layer->w/2,40,makecol(230,230,230),-1);
			textout_centre_ex(layer,megaFont,"This engine is free and open source",		layer->w/2,50,makecol(230,230,230),-1);
			textout_centre_ex(layer,megaFont,"If you paid for this you were fooled",	layer->w/2,60,makecol(230,230,230),-1);
			textout_centre_ex(layer,megaFont,"Any comment, sugestion or greetings:",	layer->w/2,70,makecol(230,230,230),-1);
			textout_centre_ex(layer,megaFont,"aniquilatorbloody@gmail.com",			layer->w/2,80,makecol(230,230,230),-1);
			textout_centre_ex(layer,megaFont,"Megaman is a trademark of",			layer->w/2,100,makecol(230,230,230),-1);
		
			gorgonShowAnimation(layer,&animationPack.animation[0],&spritePack,NULL,NORMAL,(layer->w-spritePack.sprite[6].image->w)/2,layer->h/2);
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
 * @author:	Cantídio Oliveira Fontes
 * @since: 	25/06/2008
 * @final: 	06/07/2008
 * @param: 	inputControl *, ponteiro para a estrutura de controle
 * @return:	int a opção escolhida no menu
 */
int mainMenu(inputControl *control,gorgonAudio *audio)
{
	gorgonSpritePack 	spritePack;
	gorgonAnimationPack	animationPack;
	gorgonSound		*change;
	gorgonSound		*choose;
	BITMAP 			*layer;
	FONT			*megaFont;
	int 			selected=0;
	gorgonLoadSpritePack(&spritePack,"./resource/intro.spk");
	gorgonLoadAnimationPack(&animationPack,"./resource/intro.apk");
	gorgonLoadSound(&change,"./resource/sons/mmse003.wav",audio);
	gorgonLoadSound(&choose,"./resource/sons/mmse011.wav",audio);

	megaFont= load_bitmap_font("./resource/font.pcx",NULL,NULL);
	layer	= create_bitmap(screen->w,screen->h);
	if(layer!=NULL)
	{
		timer=0;
		clear_keybuf();
		key[control->start]=0;
		while(!key[control->start])
		{
			while(timer>0)
			{
				if(key[control->up])
				{
					gorgonPlaySound(change,audio,3);
					if(selected>0) selected--;
					else selected=3;
					key[control->up]=0;
				}
				else if(key[control->down])
				{
					gorgonPlaySound(change,audio,3);
					if(selected<3) selected++;
					else selected=0;
					key[control->down]=0;
				}
				else if(key[KEY_F10])
				{
					takeShot();
					key[KEY_F10]=0;
				}
				clear(layer);
				gorgonShowAnimation(layer,&animationPack.animation[2],&spritePack,NULL,NORMAL,56,68);
				gorgonShowAnimation(layer,&animationPack.animation[4],&spritePack,NULL,NORMAL,163,97);
				gorgonShowAnimation(layer,&animationPack.animation[5],&spritePack,NULL,NORMAL,2,0);
				gorgonShowAnimation(layer,&animationPack.animation[6],&spritePack,NULL,NORMAL,2,225);
				gorgonShowAnimation(layer,&animationPack.animation[7],&spritePack,NULL,NORMAL,3,16);
				gorgonShowAnimation(layer,&animationPack.animation[7],&spritePack,NULL,NORMAL,306,16);
								
				textout_ex(layer,megaFont,"Start Game",	110,130,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Options",	110,140,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Credits",	110,150,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Exit",	110,160,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,">",		100,130 + selected*10,makecol(230,230,230),-1);
				blit(layer,screen,0,0,0,0,layer->w,layer->h);
				timer--;
			}
		}
		gorgonPlaySound(choose,audio,3);
		wait(1);
		destroy_bitmap(layer);
		gorgonDestroySpritePack(&spritePack);
		gorgonDestroyAnimationPack(&animationPack);
		gorgonDestroySound(change);
		gorgonDestroySound(choose);
		destroy_font(megaFont);
		return selected;
	}
	printf("erro ao alocar memória\n");
	exit(1);
}
/**
 * função que exibe o menu para configuração do som no jogo
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	06/07/2008
 * @param:	inputControl *, ponteiro para a estrutura de controles
 * @param:	gorgonAudio *, ponteiro para o sistema sonoro
 * @return:	int 0 se ocorreu erro ou 1 se ocorreu tudo bem
 */
int optionMenu(inputControl *control,gorgonAudio *audio)
{
	gorgonSpritePack	spritePack;
	gorgonAnimationPack	animationPack;
	gorgonSound		*change;
	gorgonSound		*choose;
	BITMAP 			*layer;
	FONT			*megaFont;
	int 			selected= 0;
	
	gorgonLoadSpritePack(&spritePack,"./resource/intro.spk");
	gorgonLoadAnimationPack(&animationPack,"./resource/intro.apk");
	gorgonLoadSound(&change,"./resource/sons/mmse003.wav",audio);
	gorgonLoadSound(&choose,"./resource/sons/mmse011.wav",audio);

	megaFont		= load_bitmap_font("./resource/font.pcx",NULL,NULL);
	layer			= create_bitmap(screen->w,screen->h);
	key[control->start]	= 0;
	if(layer!=NULL)
	{
		timer=0;
		while(!(key[control->start]))
		{
			while(timer>0)
			{
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
				else if(key[KEY_F10])
				{
					takeShot();
					key[KEY_F10]=0;
				}
				clear(layer);
				gorgonShowAnimation(layer,&animationPack.animation[5],&spritePack,NULL,NORMAL,2,0);
				gorgonShowAnimation(layer,&animationPack.animation[6],&spritePack,NULL,NORMAL,2,225);
				gorgonShowAnimation(layer,&animationPack.animation[7],&spritePack,NULL,NORMAL,3,16);
				gorgonShowAnimation(layer,&animationPack.animation[7],&spritePack,NULL,NORMAL,306,16);
				
				textout_centre_ex(layer,megaFont,"Game Options",	layer->w/2,20,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Configuration",		110,90,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Controls",			110,100,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Sound",			110,110,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Exit",			110,120,makecol(230,230,230),-1);
				
				textout_ex(layer,megaFont,">",		80,100 + selected*10,makecol(230,230,230),-1);
				blit(layer,screen,0,0,0,0,layer->w,layer->h);
				timer--;
			}
		}
		gorgonPlaySound(choose,audio,3);
		wait(1);
		destroy_bitmap(layer);
		gorgonDestroySpritePack(&spritePack);
		gorgonDestroyAnimationPack(&animationPack);
		gorgonDestroySound(change);
		gorgonDestroySound(choose);
		destroy_font(megaFont);
		return selected;
	}
	printf("erro ao alocar memória\n");
	return 0;
}

/**
 * função que exibe o menu para configuração das teclas usadas no jogo
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since: 	25/06/2008
 * @final: 	06/07/2008
 * @param: 	inputControl *, ponteiro para a estrutura de controles
 * @return: 	int 0 se ocorreu erro ou 1 se ocorreu tudo bem
 */
int controlMenu(inputControl *control,gorgonAudio *audio)
{
	gorgonSpritePack	spritePack;
	gorgonAnimationPack	animationPack;
	BITMAP 			*layer;
	FONT			*megaFont;
	gorgonSound		*change;
	gorgonSound		*choose;
	int 			selected= 0;
	
	gorgonLoadSpritePack(&spritePack,"./resource/intro.spk");
	gorgonLoadAnimationPack(&animationPack,"./resource/intro.apk");
	gorgonLoadSound(&change,"./resource/sons/mmse003.wav",audio);
	gorgonLoadSound(&choose,"./resource/sons/mmse011.wav",audio);

	megaFont		= load_bitmap_font("./resource/font.pcx",NULL,NULL);
	layer			= create_bitmap(screen->w,screen->h);
	key[control->start]	= 0;
	if(layer!=NULL)
	{
		timer=0;
		while(!(key[control->start] && selected==8))
		{
			while(timer>0)
			{
				if(key[control->up])
				{
					gorgonPlaySound(change,audio,3);
					if(selected>0) selected--;
					else selected=8;
					key[control->up]=0;
				}
				else if(key[control->down])
				{
					gorgonPlaySound(change,audio,3);
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
				else if(key[KEY_F10])
				{
					takeShot();
					key[KEY_F10]=0;
				}
				clear(layer);
				gorgonShowAnimation(layer,&animationPack.animation[5],&spritePack,NULL,NORMAL,2,0);
				gorgonShowAnimation(layer,&animationPack.animation[6],&spritePack,NULL,NORMAL,2,225);
				gorgonShowAnimation(layer,&animationPack.animation[7],&spritePack,NULL,NORMAL,3,16);
				gorgonShowAnimation(layer,&animationPack.animation[7],&spritePack,NULL,NORMAL,306,16);
				
				textout_centre_ex(layer,megaFont,"Control Configuration",	layer->w/2,20,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Up",					50,70,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Down",				50,80,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Left",				50,90,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Right",				50,100,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Shot",				50,110,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Jump",				50,120,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Next Weapon",			50,130,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Previous Weapon",			50,140,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Exit",				50,150,makecol(230,230,230),-1);
	
				textprintf_ex(layer,megaFont,240,70,makecol(230,230,230),-1,"%s",scancode_to_name(control->up));
				textprintf_ex(layer,megaFont,240,80,makecol(230,230,230),-1,"%s",scancode_to_name(control->down));
				textprintf_ex(layer,megaFont,240,90,makecol(230,230,230),-1,"%s",scancode_to_name(control->left));
				textprintf_ex(layer,megaFont,240,100,makecol(230,230,230),-1,"%s",scancode_to_name(control->right));
				textprintf_ex(layer,megaFont,240,110,makecol(230,230,230),-1,"%s",scancode_to_name(control->shot));
				textprintf_ex(layer,megaFont,240,120,makecol(230,230,230),-1,"%s",scancode_to_name(control->jump));
				textprintf_ex(layer,megaFont,240,130,makecol(230,230,230),-1,"%s",scancode_to_name(control->weaponF));
				textprintf_ex(layer,megaFont,240,140,makecol(230,230,230),-1,"%s",scancode_to_name(control->weaponB));
		

				textout_ex(layer,megaFont,">",		40,70 + selected*10,makecol(230,230,230),-1);
				blit(layer,screen,0,0,0,0,layer->w,layer->h);
				timer--;
			}
		}
		gorgonPlaySound(choose,audio,3);
		wait(1);
		destroy_bitmap(layer);
		gorgonDestroySpritePack(&spritePack);
		gorgonDestroyAnimationPack(&animationPack);
		gorgonDestroySound(change);
		gorgonDestroySound(choose);
		destroy_font(megaFont);
		return 1;
	}
	printf("erro ao alocar memória\n");
	return 0;
}

/**
 * função que exibe o menu para configuração do som no jogo
 *
 * @author:	Cantídio Oliveira Fontes
 * @since:	04/07/2008
 * @final:	06/07/2008
 * @param:	inputControl *, ponteiro para a estrutura de controles
 * @param:	gorgonAudio *, ponteiro para o sistema sonoro
 * @return:	int 0 se ocorreu erro ou 1 se ocorreu tudo bem
 */
int soundMenu(inputControl *control,gorgonAudio *audio)
{
	gorgonSpritePack	spritePack;
	gorgonAnimationPack	animationPack;
	gorgonSound		*change;
	gorgonSound		*choose;
	BITMAP 			*layer;
	FONT			*megaFont;
	int 			selected= 0;
	
	gorgonLoadSpritePack(&spritePack,"./resource/intro.spk");
	gorgonLoadAnimationPack(&animationPack,"./resource/intro.apk");
	gorgonLoadSound(&change,"./resource/sons/mmse003.wav",audio);
	gorgonLoadSound(&choose,"./resource/sons/mmse011.wav",audio);

	megaFont		= load_bitmap_font("./resource/font.pcx",NULL,NULL);
	layer			= create_bitmap(screen->w,screen->h);
	key[control->start]	= 0;
	if(layer!=NULL)
	{
		timer=0;
		while(!(key[control->start] && selected==6))
		{
			while(timer>0)
			{
				if(key[control->up])
				{
					gorgonPlaySound(change,audio,3);
					if(selected>0) selected--;
					else selected=6;
					key[control->up]=0;
				}
				else if(key[control->down])
				{
					gorgonPlaySound(change,audio,3);
					if(selected<6) selected++;
					else selected=0;
					key[control->down]=0;
				}
				else if(key[control->left])
				{
					switch(selected)
					{
						case 0:
							if(audio->music)	audio->music=0;
							else			audio->music=1;
							break;
						case 1:
							if(audio->voice)	audio->voice=0;
							else			audio->voice=1;
							break;
						case 2:
							if(audio->effects)	audio->effects=0;
							else			audio->effects=1;
							break;
						case 3:
							if(audio->musicVolume>0)	audio->musicVolume-=0.01;
							break;
						case 4:
							if(audio->voiceVolume>0)	audio->voiceVolume-=0.01;
							break;
						case 5:
							if(audio->effectsVolume>0)	audio->effectsVolume-=0.01;
							break;
					}
					key[control->left]=0;
				}
				else if(key[control->right])
				{
					switch(selected)
					{
						case 0:
							if(audio->music)	audio->music=0;
							else			audio->music=1;
							break;
						case 1:
							if(audio->voice)	audio->voice=0;
							else			audio->voice=1;
							break;
						case 2:
							if(audio->effects)	audio->effects=0;
							else			audio->effects=1;
							break;
						case 3:
							if(audio->musicVolume<1)	audio->musicVolume+=0.01;
							break;
						case 4:
							if(audio->voiceVolume<1)	audio->voiceVolume+=0.01;
							break;
						case 5:
							if(audio->effectsVolume<1)	audio->effectsVolume+=0.01;
							break;
					}
					key[control->right]=0;
				}
				else if(key[KEY_F10])
				{
					takeShot();
					key[KEY_F10]=0;
				}
				clear(layer);
				gorgonShowAnimation(layer,&animationPack.animation[5],&spritePack,NULL,NORMAL,2,0);
				gorgonShowAnimation(layer,&animationPack.animation[6],&spritePack,NULL,NORMAL,2,225);
				gorgonShowAnimation(layer,&animationPack.animation[7],&spritePack,NULL,NORMAL,3,16);
				gorgonShowAnimation(layer,&animationPack.animation[7],&spritePack,NULL,NORMAL,306,16);
				
				textout_centre_ex(layer,megaFont,"Sound Configuration",	layer->w/2,20,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Use Channels",		50,70,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Music",			50,80,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Voice",			50,90,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Effects",			50,100,makecol(230,230,230),-1);
				
				textout_ex(layer,megaFont,"Sound Volume",		50,120,makecol(230,230,230),-1);	
				textout_ex(layer,megaFont,"Music",			50,130,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Voice",			50,140,makecol(230,230,230),-1);
				textout_ex(layer,megaFont,"Effects",			50,150,makecol(230,230,230),-1);
				
				textout_ex(layer,megaFont,"Exit",			50,160,makecol(230,230,230),-1);
	
				textprintf_ex(layer,megaFont,240,80,makecol(230,230,230),-1,"%s",(audio->music)		? "Yes" : "No");
				textprintf_ex(layer,megaFont,240,90,makecol(230,230,230),-1,"%s",(audio->voice)		? "Yes" : "No");
				textprintf_ex(layer,megaFont,240,100,makecol(230,230,230),-1,"%s",(audio->effects)	? "Yes" : "No");
			
				textprintf_ex(layer,megaFont,240,130,makecol(230,230,230),-1,"%d",(int)(audio->musicVolume*100));
				textprintf_ex(layer,megaFont,240,140,makecol(230,230,230),-1,"%d",(int)(audio->voiceVolume*100));
				textprintf_ex(layer,megaFont,240,150,makecol(230,230,230),-1,"%d",(int)(audio->effectsVolume*100));

				textout_ex(layer,megaFont,">",		40,((selected<3) ? (80 + selected*10) : (80 + 20 + selected*10)),makecol(230,230,230),-1);
				blit(layer,screen,0,0,0,0,layer->w,layer->h);
				timer--;
			}
		}
		gorgonPlaySound(choose,audio,3);
		wait(1);
		destroy_bitmap(layer);
		gorgonDestroySpritePack(&spritePack);
		gorgonDestroyAnimationPack(&animationPack);
		gorgonDestroySound(change);
		gorgonDestroySound(choose);
		destroy_font(megaFont);
		return 1;
	}
	printf("erro ao alocar memória\n");
	return 0;
}
/**
 * função que exibe os creditos
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 25/06/2008
 * @final: 06/07/2008
 * @param: inputControl *, ponteiro para a estrutura de controles
 * @return: int 0 se ocorreu erro ou 1 se ocorreu tudo bem
 */
void credits(inputControl *control)
{
	BITMAP	*layer;
	FONT	*megaFont;
	
	megaFont		= load_bitmap_font("./resource/font.pcx",NULL,NULL);
	layer			= create_bitmap(screen->w,screen->h);
	key[control->start]	= 0;
	while(!(key[control->start]))
	{
		if(key[KEY_F10])
		{
			takeShot();
			key[KEY_F10]=0;
		}
		clear(layer);
		textout_centre_ex(layer,megaFont,"Credits:"				,layer->w/2,10,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"Engine Programming:"			,layer->w/2,30,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"Cantidio Oliveira Fontes"		,layer->w/2,40,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"aniquilatorbloody@gmail.com"		,layer->w/2,50,makecol(230,230,230),-1);
		
		textout_centre_ex(layer,megaFont,"Menu Layout:"				,layer->w/2,70,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"Rafael Menezes"			,layer->w/2,80,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"rafa.oblong@gmail.com"		,layer->w/2,90,makecol(230,230,230),-1);
		
		
		textout_centre_ex(layer,megaFont,"Sprite Ripping:"			,layer->w/2,110,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"Sprites INC"				,layer->w/2,120,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"www.sprites-inc.co.uk"		,layer->w/2,130,makecol(230,230,230),-1);

		textout_centre_ex(layer,megaFont,"Music Ripping:"			,layer->w/2,150,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"The MegaMan Network"			,layer->w/2,160,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"blue-bomber.jvmwriter.org"		,layer->w/2,170,makecol(230,230,230),-1);
		
		textout_centre_ex(layer,megaFont,"Megaman and all related characters are"	,layer->w/2,190,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"registered trademarks of Capcom"		,layer->w/2,200,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"www.capcom.com"				,layer->w/2,210,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"This engine is no way related to Capcom"	,layer->w/2,220,makecol(230,230,230),-1);
		textout_centre_ex(layer,megaFont,"All rights are reserved"			,layer->w/2,230,makecol(230,230,230),-1);
		
		
		
		blit(layer,screen,0,0,0,0,layer->w,layer->h);
	}
	destroy_font(megaFont);
	destroy_bitmap(layer);
}
