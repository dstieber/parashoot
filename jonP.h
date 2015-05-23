/*
Program: Hw 3/Lab 06
Author: Jonathan Popkin
Purpose: The purpose of this lab is to seperate game files
*/
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
void InitBlueBird2();
void MakeBlueBird(Game *game);
void MakeBlueBird2(Game *game);
void BlueBirdMovement(Game *game);
void BlueBirdMovement2(Game *game);
void BlueBirdRender(Game *game);
void BlueBirdRender2(Game *game);
extern void deleteBlueBird(Game *game, Bird *node);
#endif
