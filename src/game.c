#include "../../gorgon_core/include/gorgon.h"
#include "../include/control.h"
#include "../include/timer.h"
#include "../include/background.h"
#include "../include/weapon.h"
#include "../include/player.h"
#include "../include/gui.h"
#include "../include/menu.h"


#define SIZEX 320
#define SIZEY 240

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
 * função para iniciar o modo allegro
 *
 * @author: Cantídio Oliveira Fontes
 * @since: 22/06/2008
 */
void init()//inicialização do allegro
{
	int depth, res;
	allegro_init();
	depth = desktop_color_depth();
	if (depth == 0) depth = 24;
	set_color_depth(depth);
	res = set_gfx_mode(GFX_AUTODETECT_WINDOWED, SIZEX, SIZEY, 0, 0);
	set_window_title("megaman from hell");
	if (res != 0)
	{
		allegro_message(allegro_error);
		exit(-1);
	}
	install_timer();
	install_keyboard();
	LOCK_VARIABLE(timer);
	LOCK_FUNCTION(game_time);
	install_int_ex(game_time, BPS_TO_TIMER(40));
}
/**
 * função para rodar o loop principal do jogo
 *
 * @author: Cantídio oliveira Fontes
 * @since: 25/06/2008
 * @final: 25/06/2008
 * @param: megaman *, ponteiro para o megaman
 * @param: background *, ponteiro para o cenário que o megaman será exibido
 */
void gameLoop(megaman *mega,background *bg,gorgonAudio *audio)
{
	BITMAP *buffer;
	megamanGui gui;
	createGui(&gui);	
	buffer=create_bitmap(320,240);
	int backupTime=0;	

	timer=0;
	key[mega->controlDef.start]=0;
	while(!key[KEY_ESC])
	{
		while(timer>=0)
		{
			if(key[mega->controlDef.start])
			{
				key[mega->controlDef.start]=0;
				backupTime=timer;
				while(!key[mega->controlDef.start]){}//mostrar menu no lugar disso aki
				timer=backupTime;
				key[mega->controlDef.start]=0;
			} else if(key[KEY_F10])
			{
				takeShot();
				key[KEY_F10]=0;
			}
				
			clear_to_color(buffer,makecol(0,111,0));
			megamanNormalEvents(mega,bg,audio);
			weaponsNormalEvents(&mega->weapons,bg);

			gorgonDrawBackground(buffer,&bg->bg,BACK_LAYERS);
			megamanDraw(buffer,mega,bg);
			weaponsDraw(buffer,&mega->weapons,bg);
			gorgonDrawBackground(buffer,&bg->bg,FRONT_LAYERS);
			
			guiDraw(buffer,&gui,mega);
//			desenhacol(buffer,&bg->bg);
//	country crows
			blit(buffer,screen,0,0,0,0,320,240);
			timer--;
		}
	}
	destroy_bitmap(buffer);
}

int main(int argc, char *argv[])
{
	gorgonAudio	audio;
	inputControl	control;
	megaman 	mega;
	int 		exit=0; int debug=0;
	background bg;
	BITMAP *layer;

	init();
	loadControlDef(&control);
	printf("%d\n",gorgonCreateSoundSystem(&audio,"audio.bin"));
	showLogos(&control);
	do
	{
		switch(mainMenu(&control,&audio))
		{
			case 0:
				createMegaman(&mega,&control,&audio);
				createBackground(&bg,YAMATTO);
				gameLoop(&mega,&bg,&audio);
				destroyBackground(&bg);
				destroyMegaman(&mega);
				break;
			case 1: //option
				optionMenu(&control,&audio);
				saveControlDef(&control);
				break;
			case 2:
				credits(&control);
				break;
			case 3: //exit
				exit=1;
		}
	}while(exit==0);
	gorgonDestroySoundSystem(&audio);
	return 0;
}
