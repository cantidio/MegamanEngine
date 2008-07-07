#include "../../gorgon_core/include/gorgon.h"
#include "../include/debug.h"
#include "../include/control.h"
#include "../include/timer.h"
#include "../include/background.h"
#include "../include/weapon.h"
#include "../include/player.h"
#include "../include/gui.h"
#include "../include/menu.h"
#include "../include/enemy_jack.h"


#define SIZEX 320
#define SIZEY 240

/**
 * função para iniciar o modo allegro
 *
 * @author: 	Cantídio Oliveira Fontes
 * @since: 	22/06/2008
 * @final:	22/06/2008
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
 * @author:	Cantídio oliveira Fontes
 * @since: 	25/06/2008
 * @final: 	06/07/2008
 * @param: 	megaman *, ponteiro para o megaman
 * @param: 	background *, ponteiro para o cenário que o megaman será exibido
 */
void gameLoop(megaman *mega,background *bg,gorgonAudio *audio)
{
	BITMAP *buffer;
	enemyJackPack jackPack;
	megamanGui gui;
	createGui(&gui);	
	buffer=create_bitmap(320,240);
	int backupTime=0;	

	timer=0;
	key[mega->controlDef.start]=0;
	gorgonPlaySound(bg->music,audio,GORGON_MUSIC);
	createEnemyJack(&jackPack,audio,6);
	createJack(&jackPack,180,159);
	createJack(&jackPack,230,127);
	createJack(&jackPack,360,79);
	createJack(&jackPack,460,111);
	createJack(&jackPack,635,111);
	createJack(&jackPack,727,191);
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
			else if(key[KEY_D] && key[KEY_SPACE])
			{
				key[KEY_SPACE]	= 0;
				key[KEY_D]	= 0;
				toogleDebug();
			}
				
			clear_to_color(buffer,makecol(0,111,0));
			if(megamanIsDead(mega)) key[KEY_ESC]=1;

			jackPackNormalEvents(&jackPack,bg,mega);
			megamanNormalEvents(mega,bg);
			weaponsNormalEvents(&mega->weapons,bg);

			gorgonDrawBackground(buffer,&bg->bg,BACK_LAYERS);//parte do cenário que fica atraz do personagens
			drawClsn(buffer,bg);				//desenha as caixas de colisão do cenário
			
			jackDraw(buffer,&jackPack,bg);
			megamanDraw(buffer,mega,bg);
			weaponsDraw(buffer,&mega->weapons,bg);
			
			gorgonDrawBackground(buffer,&bg->bg,FRONT_LAYERS);//parte do cenário a frente do personagem
			guiDraw(buffer,&gui,mega);
			blit(buffer,screen,0,0,0,0,320,240);
			timer--;
		}
	}
	destroyEnemyJack(&jackPack);
	gorgonStopChannel(audio,GORGON_MUSIC);
	destroy_bitmap(buffer);
}

int main(int argc, char *argv[])
{
	gorgonAudio	audio;
	inputControl	control;
	megaman 	mega;
	int 		exit=0;
	int 		debug=0;
	background bg;
	BITMAP *layer;

	init();
	loadControlDef(&control);
	gorgonCreateSoundSystem(&audio,"audio.bin");
	showLogos(&control);
	do
	{
		switch(mainMenu(&control,&audio))
		{
			case 0:
				createMegaman(&mega,&control,&audio);
				createBackground(&bg,&audio,YAMATTO);
				gameLoop(&mega,&bg,&audio);
				destroyBackground(&bg);
				destroyMegaman(&mega);
				break;
			case 1: //option
				do
				{
					switch(optionMenu(&control,&audio))
					{
						case 0://configuração de controles
							controlMenu(&control,&audio);
							saveControlDef(&control);
							break;
						case 1://configuração de audio
							soundMenu(&control,&audio);
							gorgonSaveAudioConfigBin(&audio,"audio.bin");
							break;
						case 2://sair do menu
							exit=1;
							break;
					}
				}while(exit==0);
				exit=0;
				break;
			case 2://mostrar créditos
				credits(&control);
				break;
			case 3: //exit
				exit=1;
		}
	}while(exit==0);
	gorgonDestroySoundSystem(&audio);
	return 0;
}
