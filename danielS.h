/*
 * Filename:	danielS.h
 * Author:		Daniel Stieber
 * Purpose:		This is the header file for danielS.cpp.
 * 
 */

#ifndef _DANIELS_H_
#define _DANIELS_H_

#include "types.h"

extern Game game;
extern int xres, yres;
extern unsigned char *buildAlphaData(Ppmimage *img);
void initSky(void);
void renderSky(Game *game);
void initCharacter(void);
void renderCharacter(Game *game);
void displayAltitude(Game *game);
void renderStartMenu(Game *game);
void randomGenerator(Game *game);
extern void BlueBirdRender(Game *game);
extern void MakeBlueBird(Game *game);
void deleteBlueBird(Game *game, Bird *node);
void deleteMissile(Game *game, Missile *node);
#endif
