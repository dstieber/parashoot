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
extern GLuint BirdTsilhouetteTexture;
void play();
void create_sounds();
void MakeBlueBird(Game *game);
void BlueBirdMovement(Game *game);
void renderBlueBird(Game *game);
void renderBlueBird2(Game *game);
#endif
