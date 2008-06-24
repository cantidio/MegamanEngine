#include "../include/control.h"
#include "../include/background.h"
#include "../include/weapon.h"
#include "../include/player.h"

#define SIZEX 320
#define SIZEY 240

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
}
int main()
{
	megaman mega;
	background bg;
	BITMAP *buffer;	
	init();
	printf("%d\n",createBackground(&bg));
	createMegaman(&mega);
		
	buffer=create_bitmap(320,240);
	while(!key[KEY_ESC])
	{
		clear(buffer);
		//if(key[KEY_RIGHT] && mega.animationPlaying< mega.animationPack.animationNumber-1) mega.animationPlaying++;
		//else if(key[KEY_LEFT] && mega.animationPlaying>0) mega.animationPlaying--;
		megamanNormalEvents(&mega,&bg);

		gorgonDrawBackground(buffer,&bg.bg,BACK_LAYERS);
		megamanDraw(buffer,&mega);
		gorgonDrawBackground(buffer,&bg.bg,FRONT_LAYERS);
		blit(buffer,screen,0,0,0,0,320,240);
		rest(30);
	}
	destroy_bitmap(buffer);
	unloadMegaman(&mega);
}