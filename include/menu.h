#ifndef MENUF
#define MENUF
#include "../../gorgon_core/include/gorgon.h"
#include "control.h"
#include "timer.h"
void	takeShot();
int 	showLogos(inputControl *control);
int 	mainMenu(inputControl *control,gorgonAudio *audio);
int 	optionMenu(inputControl *control,gorgonAudio *audio);
int 	controlMenu(inputControl *control,gorgonAudio *audio);
int 	soundMenu(inputControl *control,gorgonAudio *audio);
void 	credits(inputControl *control);
#endif
