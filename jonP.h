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
void InitBlueBird(void);
void MakeBlueBird(Game *game);
void MakeRedBird(Game *game);
void RedBirdMovement(Game *game);
void BlueBirdMovement(Game *game);
void BlueBirdMovement2(Game *game);
void BlueBirdRender(Game *game);
void BlueBirdRender2(Game *game);
void renderRedBird(Game *game);
extern void deleteBlueBird(Game *game, Bird *node);
extern void deleteRedBird(Game *game, Bird2 *node);
#endif
