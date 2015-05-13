/* Program : Homework 3 / Lab6
 * Author  : Michael Harp
 * Purpose : Render mountain, initialize keys, check keys functions
 */
#ifndef _MICHAELH_H_
#define _MICHAELH_H_

#include "types.h"

extern int keys[65536];
extern XEvent e;
extern Game game;
extern int xres, yres;
extern GLuint mountainTexture, msilhouetteTexture;
extern unsigned char *buildAlphaData(Ppmimage *img);

void renderMountain(Game *game);

void InitMountain();
void InitMissile();
void MakeMissile(Game *game);
void MissileMovement(Game *game);
void MissileRender(Game *game);

void init_keys();
int check_keys(XEvent *e);

#endif
