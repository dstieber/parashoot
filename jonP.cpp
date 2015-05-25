/*
Program : Homework 3/Lab 6
Author : Jonathan Popkin
Purpose: The Purpose of this lab is to seperate game files
*/ 
#include "jonP.h"

Ppmimage *BlueBirdImage = NULL;
GLuint BsilhouetteTexture;

Ppmimage *BlueBirdImage2 = NULL;
GLuint BsilhouetteTexture2;

Ppmimage *LogoImage= NULL;
GLuint LsilhouetteTexture;

void InitBlueBird()
{

    BlueBirdImage = ppm6GetImage("./images/BlueBird.ppm");
    glGenTextures(1, &BsilhouetteTexture);
    //
    //BlueBird
    glBindTexture(GL_TEXTURE_2D, BsilhouetteTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *BsilhouetteData = buildAlphaData(BlueBirdImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BlueBirdImage->width,
	    BlueBirdImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	    BsilhouetteData);
    delete [] BsilhouetteData;

}
void InitBlueBird2()
{
    BlueBirdImage2 = ppm6GetImage("./images/BlueBird2.ppm");
    glGenTextures(1, &BsilhouetteTexture2);
    //
    //BlueBird
    glBindTexture(GL_TEXTURE_2D, BsilhouetteTexture2);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *BsilhouetteData2 = buildAlphaData(BlueBirdImage2);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BlueBirdImage2->width,
	    BlueBirdImage2->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	    BsilhouetteData2);
    delete [] BsilhouetteData2;



}
void InitLogo()
{
    LogoImage = ppm6GetImage("./images/LogoWhite.ppm");
    glGenTextures(1, &LsilhouetteTexture);
    //
    //White Logo
    glBindTexture(GL_TEXTURE_2D, LsilhouetteTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *LsilhouetteData = buildAlphaData(LogoImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, LogoImage->width,
	    LogoImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	    LsilhouetteData);
    delete [] LsilhouetteData;



}


void MakeBlueBird(Game *game) 
{
    Character *b;

    b = &game->BlueBird;
    b->s.center.x = xres/2-400;
    b->s.center.y = (game->altitude- (yres/2)+10);
    b->velocity.x =0;
    b->velocity.y = 0;
}

void MakeBlueBird2(Game *game) 
{
    Character *b;

    b = &game->BlueBird2[game->n];
    b->s.center.x = xres/2+400;
    b->s.center.y = (game->altitude- (yres/2)+50);
    b->velocity.x =0;
    b->velocity.y = 0;
    game->n++;
}

void MakeLogo(Game *game)
{
   Object *l;

  l = &game->Logo;
  l->s.center.x = xres/2+2;
  l->s.center.y = (game->altitude - (yres/2)+30);

}

void BlueBirdMovement(Game *game)
{
    Character *b;
    b= &game->BlueBird;
    b->s.center.x += b->velocity.x;
    b->s.center.y += b->velocity.y;
    b->s.center.y -= GRAVITY;

}

void BlueBirdMovement2(Game *game)
{
    Character *b;
    for(int i=0; i < game->n; i++) {
    b= &game->BlueBird2[i];
    b->s.center.x += b->velocity.x;
    b->s.center.y += b->velocity.y;
    b->s.center.y -= GRAVITY;
    }

}


void BlueBirdRender(Game *game)
{
    int wB= 17;
    int hB= 13;

    if(game->altitude < 11500 && game->altitude > 10000)
    {
	Character *bv;
	Vec *b;
	b = &game->BlueBird.s.center;
	bv = &game->BlueBird;

	glBindTexture(GL_TEXTURE_2D, BsilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f); //0.0f
	glColor4ub(255, 255, 255, 255); //255 255 255 255
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(b->x-wB, b->y-hB);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(b->x-wB, b->y+hB);
	glTexCoord2f(0.5f, 0.0f); glVertex2i(b->x+wB, b->y+hB);
	glTexCoord2f(0.5f, 1.0f); glVertex2i(b->x+wB, b->y-hB);
	glEnd();

	bv->velocity.x = 9;
    }
}
void BlueBirdRender2(Game *game)
{
    int wB= 17;
    int hB= 13;

    for(int i=0; i < game->n; i++) {
    /*
       if (birdFires) {
       if (firstTime) { 
       float currentAltitude = game->altitude;
       firstTime = 0;
       }
       {
    //render

    firstTime = 1;
    }
    }
    */

   // if(game->altitude < 11600 && game->altitude > 10000)
   	if(rand()%100 <1) {
	    std::cout << (rand()%100);
       if ((game->altitude + yres) > game->altitude && game->altitude > (game->altitude - yres))
    
       {
	//MakeBlueBird2(game);
//	BlueBirdMovement(game);
	Character *bv;
	Vec *b;
	b = &game->BlueBird2[i].s.center;
	bv = &game->BlueBird2[i];

	glBindTexture(GL_TEXTURE_2D, BsilhouetteTexture2);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(0, 0, 0, 0); //255 255 255 255
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(b->x-wB, b->y-hB);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(b->x-wB, b->y+hB);
	glTexCoord2f(0.5f, 0.0f); glVertex2i(b->x+wB, b->y+hB);
	glTexCoord2f(0.5f, 1.0f); glVertex2i(b->x+wB, b->y-hB);
	glEnd();

	bv->velocity.x = -9;
    }
    }
    }

}

void LogoRender(Game *game)
{
    int w= 796;
    int h= 96;

	Vec *l;
	l = &game->Logo.s.center;

	glBindTexture(GL_TEXTURE_2D, LsilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f); //0.0f
	glColor4ub(255, 255, 255, 255); //255 255 255 255
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(l->x-w, l->y-h);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(l->x-w, l->y+h);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(l->x+w, l->y+h);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(l->x+w, l->y-h);
	glEnd();

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
