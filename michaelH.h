// Michael Harp
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
