/*
Program : Homework 3/Lab 6
Author : Jonathan Popkin
Purpose: The Purpose of this lab is to seperate game files
*/ 
#include "jonP.h"

void MakeBlueBird(Game *game) 
{
    Character *b;
    b = &game->BlueBird;

    b->s.center.x = xres/2-400;
    b->s.center.y = (game->altitude- (yres/2)+10);
    b->velocity.x =0;
    b->velocity.y = 0;
}

void BlueBirdMovement(Game *game)
{
    Character *b;
    b= &game->BlueBird;
    b->s.center.x += b->velocity.x;
    b->s.center.y += b->velocity.y;
    b->s.center.y -= GRAVITY;

}

void renderBlueBird(Game *game)
{
    int wB= 17;
    int hB= 13;

    if(game->altitude < 11500 && game->altitude > 10000)
    {
	Character *bv;
	Vec *b;
	b = &game->BlueBird.s.center;
	bv = &game->BlueBird;

	glBindTexture(GL_TEXTURE_2D, BirdTsilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(b->x-wB, b->y-hB);
	glTexCoord2f(0.0f, 0.80f); glVertex2i(b->x-wB, b->y+hB);
	glTexCoord2f(0.25f, 0.80f); glVertex2i(b->x+wB, b->y+hB);
	glTexCoord2f(0.25f, 1.0f); glVertex2i(b->x+wB, b->y-hB);
	glEnd();

	bv->velocity.x = 9;
    }
}

void renderBlueBird2(Game *game)
{
    int wB= 17;
    int hB= 13;

    /*
       if (birdFires) {
       if (firstTime) { 
       float currentAltitude = game->altitude;
       firstTime = 0;
       }
       while ((currentAltitude + yres) > currentAltitude > (currentAltitude - yres))
       {
    //render

    firstTime = 1;
    }
    }
    */

    if(game->altitude < 11600 && game->altitude > 10000)
    {
	Character *bv;
	Vec *b;
	b = &game->BlueBird.s.center;
	bv = &game->BlueBird;

	glBindTexture(GL_TEXTURE_2D, BirdTsilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.75f, 1.0f); glVertex2i(b->x-wB, b->y-hB);
	glTexCoord2f(0.75f, 0.8f); glVertex2i(b->x-wB, b->y+hB);
	glTexCoord2f(1.0f, 0.8f); glVertex2i(b->x+wB, b->y+hB);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(b->x+wB, b->y-hB);
	glEnd();

	bv->velocity.x = 9;
    }

}

void create_sounds() {
#ifdef USE_SOUND
    if(fmod_init()) {
	printf("ERROR");
	return;
    }
    if(fmod_createsound((char *)"./sounds/Highly_Suspicious.mp3", 0)) {
	printf("ERROR");
	return;
    }
    fmod_setmode(0, FMOD_LOOP_NORMAL);
#endif
}

void play() {
    //fmod_playsound(0);
}
