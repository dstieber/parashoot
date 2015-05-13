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
void renderMountain(Game *game);
void init_keys();
int check_keys(XEvent *e);

#endif
