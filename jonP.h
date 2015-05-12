#ifndef _JONP_H_
#define _JONP_H_

#include "types.h"

#define USE_SOUND
#ifdef USE_SOUND
#include <FMOD/fmod.h>
#include <FMOD/fmod_errors.h>
#include <FMOD/wincompat.h>
#include "fmod.h"
#endif

extern Game game;
extern int xres;
extern int yres;
extern unsigned char *buildAlphaData(Ppmimage *img);
void play();
void create_sounds();
void InitBlueBird();
void MakeBlueBird(Game *game);
void BlueBirdMovement(Game *game);
void BlueBirdRender(Game *game);
#endif
