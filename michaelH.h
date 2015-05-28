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

void InitMountain();
void MakeMountain(Game *game);
void MountainMovement(Game *game);
void renderMountain(Game *game);

void InitMissile();
void MakeMissile(Game *game);
void MissileMovement(Game *game);
void MissileRender(Game *game);
extern void deleteMissile(Game *game, Missile *node);

void InitCloud();
void MakeCloud(Game *game);
void CloudMovement(Game *game);
void renderCloud(Game *game);

void InitCloud2();
void MakeCloud2(Game *game);
void Cloud2Movement(Game *game);
void renderCloud2(Game *game);

void InitPlane();
void MakePlane(Game *game);
void PlaneMovement(Game *game);
void renderPlane(Game *game);

void init_keys();
int check_keys(XEvent *e);

#endif
