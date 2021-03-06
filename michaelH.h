/* Program : Homework 3 / Lab6
 * Author  : Michael Harp
 * Purpose : Render mountain, initialize keys, check keys functions
 */
#ifndef _MICHAELH_H_
#define _MICHAELH_H_

#include "types.h"
extern float GRAVITY;
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

void deleteCloud(Game *game, Cloud *node);
void MakeRandomCloud(Game *game);
void randomCloudMovement(Game *game);
void renderRandomCloud(Game *game);

void deletePlane(Game *game, Planes *node);
void MakeRandomPlane(Game *game);
void randomPlaneMovement(Game *game);
void renderRandomPlane(Game *game);

void renderScore(Game *game);
void MakeGreenBird(Game *game);
void MakeOrangeBird(Game *game);
void MakePurpleBird(Game *game);

void MakeBlueMissile(Game *game);
void MakeYellowMissile(Game *game);
void MakeRedMissile(Game *game);

void init_keys();
int check_keys(XEvent *e);
extern void cleanupBlueBirds(Game *game);
extern void cleanupRandomClouds(Game *game);
extern void cleanupPlanes(Game *game);
extern void cleanupMissiles(Game *game);
#endif
