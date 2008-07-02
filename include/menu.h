#ifndef MENUF
#define MENUF
#include "../../gorgon_core/include/gorgon.h"
#include "../../gorgon_core/include/gorgon_sound.h"
#include "control.h"
#include "timer.h"
int showLogos(inputControl *control);
int mainMenu(inputControl *control,gorgonAudio *audio);
int optionMenu(inputControl *control,gorgonAudio *audio);
void credits(inputControl *control);
#endif
