/*
 * Filename:	danielS.cpp
 * Author:		Daniel Stieber
 * Purpose:		This cpp file defines functions declared in danielS.h
 *
 */

#include "danielS.h"
Ppmimage *skyImage = NULL;
Ppmimage *characterImage = NULL;
Ppmimage *RarmImage = NULL;
Ppmimage *BodyImage = NULL;
Ppmimage *LarmImage = NULL;
Ppmimage *RlegImage = NULL;
Ppmimage *LlegImage = NULL;
Ppmimage *LimbImage = NULL;
Ppmimage *HeadImage = NULL;
GLuint skyTexture;
GLuint silhouetteTexture;
GLuint RarmTexture;
GLuint BodyTexture;
GLuint LarmTexture;
GLuint RlegTexture;
GLuint LlegTexture;
GLuint LimbTexture;
GLuint HeadTexture;

void initSky(void) 
{
    skyImage = ppm6GetImage("./images/Sunset.ppm");
    glGenTextures(1, &skyTexture);
    glBindTexture(GL_TEXTURE_2D, skyTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, skyImage->width, skyImage->height,
	    0, GL_RGB, GL_UNSIGNED_BYTE, skyImage->data);
}

void renderSky(Game *game) 
{
    glBindTexture(GL_TEXTURE_2D, skyTexture);
    glBegin(GL_QUADS);
    int ybottom = game->altitude - yres;
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, ybottom);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, game->altitude);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, game->altitude);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, ybottom);
    glEnd();
}

void initCharacter(void) 
{
    /*characterImage = ppm6GetImage("./images/character2.ppm");
    glGenTextures(1, &silhouetteTexture);
    glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *silhouetteData = buildAlphaData(characterImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, characterImage->width, 
	    characterImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
    delete [] silhouetteData;*/

    //body Texture
    BodyImage = ppm6GetImage("./images/Body.ppm");
    glGenTextures(1, &silhouetteTexture);
    glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *silhouetteData = buildAlphaData(BodyImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BodyImage->width, BodyImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
    delete [] silhouetteData;

    //head
    HeadImage = ppm6GetImage("./images/Head.ppm");
    glGenTextures(1, &HeadTexture);
    glBindTexture(GL_TEXTURE_2D, HeadTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *HeadData = buildAlphaData(HeadImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, HeadImage->width, HeadImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, HeadData);

    //Right arm
    RarmImage = ppm6GetImage("./images/Arm1.ppm");
    glGenTextures(1, &RarmTexture);
    glBindTexture(GL_TEXTURE_2D, RarmTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *RarmData = buildAlphaData(RarmImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RarmImage->width, RarmImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, RarmData);

    //Left arm
    LarmImage = ppm6GetImage("./images/Larm1.ppm");
    glGenTextures(1, &LarmTexture);
    glBindTexture(GL_TEXTURE_2D, LarmTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *LarmData = buildAlphaData(LarmImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, LarmImage->width, LarmImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LarmData);

    //Right leg
    RlegImage = ppm6GetImage("./images/Rleg.ppm");
    glGenTextures(1, &RlegTexture);
    glBindTexture(GL_TEXTURE_2D, RlegTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *RlegData = buildAlphaData(RlegImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RlegImage->width, RlegImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, RlegData);

    //Left leg
    LlegImage = ppm6GetImage("./images/Lleg.ppm");
    glGenTextures(1, &LlegTexture);
    glBindTexture(GL_TEXTURE_2D, LlegTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *LlegData = buildAlphaData(LlegImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, LlegImage->width, LlegImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LlegData);

    //Limbs
    LimbImage = ppm6GetImage("./images/Limb.ppm");
    glGenTextures(1, &LimbTexture);
    glBindTexture(GL_TEXTURE_2D, LimbTexture);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *LimbData = buildAlphaData(LimbImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, LimbImage->width, LimbImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LimbData);

}

void renderCharacter(Game *game)
{
    float w, h;
    //body
    glPushMatrix();

    Character *s1 = &game->body;
    glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glTranslatef(s1->s.c[0], s1->s.c[1], 0.0f);
    glRotatef(-s1->s.rot, 0.0f, 0.0f, 1.0f);
    w = s1->s.width;
    h = s1->s.height/2.0;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, -h);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, h);
    glTexCoord2f(0.5f, 0.0f); glVertex2i(w, h);
    glTexCoord2f(0.5f, 1.0f); glVertex2i(w, -h);
    glEnd();
    //head
      Character *s = &game->head;
      glBindTexture(GL_TEXTURE_2D, HeadTexture);
      glTranslatef(s->s.c[0], s->s.c[1], 0.0f);
      glRotatef(-s->s.rot, 0.0f, 0.0f, 1.0f);
      w = s->s.width;
      h = s->s.height;
      glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 1.0f); glVertex2f(-(float)w, h+5);
      glTexCoord2f(0.0f, 0.0f); glVertex2f(-(float)w, h+30);
      glTexCoord2f(0.5f, 0.0f); glVertex2f( (float)w, h+30);
      glTexCoord2f(0.5f, 1.0f); glVertex2f( (float)w, h+5);
      glEnd();
    //draw right arm
    glPushMatrix();
    Character *s2 = &game->rarm1;
    glBindTexture(GL_TEXTURE_2D, LimbTexture);
    glTranslatef(s2->s.c[0], s2->s.c[1], 0.0f);
    glRotatef(-s2->s.rot, 0.0f, 0.0f, 1.0f);
    w = s2->s.width;
    h = s2->s.height;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, h);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(w, h);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(w, 0);
    glEnd();
    //draw right lower arm
    glBindTexture(GL_TEXTURE_2D, RarmTexture);
    Character *s3 = &game->rarm2;
    glTranslatef(s3->s.c[0], s3->s.c[1], 0.0f);
    glRotatef(-s3->s.rot, 0.0f, 0.0f, 1.0f);
    w = s3->s.width;
    h = s3->s.height;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, h);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(w, h);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(w, 0);
    glEnd();
    glPopMatrix();
    //draw left arm
    glPushMatrix();
    Character*s4 = &game->larm1;
    glBindTexture(GL_TEXTURE_2D, LimbTexture);
    glTranslatef(s4->s.c[0], s4->s.c[1], 0.0f);
    glRotatef(-s4->s.rot, 0.0f, 0.0f, 1.0f);
    w = s4->s.width;
    h = s4->s.height;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, h);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(w, h);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(w, 0);
    glEnd();
    //draw lower left arm
    Character *s5 = &game->larm2;
    glBindTexture(GL_TEXTURE_2D, LarmTexture);
    glTranslatef(s5->s.c[0], s5->s.c[1], 0.0f);
    glRotatef(-s5->s.rot, 0.0f, 0.0f, 1.0f);
    w = s5->s.width;
    h = s5->s.height;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, h);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(w, h);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(w, 0);
    glEnd();
    glPopMatrix();
    //draw right quad
    glPushMatrix();
    Character *s6 = &game->rleg1;
    glBindTexture(GL_TEXTURE_2D, LimbTexture);
    glTranslatef(s6->s.c[0], s6->s.c[1], 0.0f);
    glRotatef(-s6->s.rot, 0.0f, 0.0f, 1.0f);
    w = s6->s.width;
    h = s6->s.height;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, h);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(w, h);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(w, 0);
    glEnd();
    //draw right shin
    Character *s7 = &game->rleg2;
    glBindTexture(GL_TEXTURE_2D, RlegTexture);
    glTranslatef(s7->s.c[0], s7->s.c[1], 0.0f);
    glRotatef(-s7->s.rot, 0.0f, 0.0f, 1.0f);
    w = s7->s.width;
    h = s7->s.height;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, h);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(w, h);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(w, 0);
    glEnd();
    glPopMatrix();
    //draw left quad
    glPushMatrix();
    Character *s8 = &game->lleg1;
    glBindTexture(GL_TEXTURE_2D, LimbTexture);
    glTranslatef(s8->s.c[0], s8->s.c[1], 0.0f);
    glRotatef(-s8->s.rot, 0.0f, 0.0f, 1.0f);
    w = s8->s.width;
    h = s8->s.height;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, 0);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, h);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(w, h);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(w, 0);
    glEnd();
    //draw left shin
    Character *s9 = &game->lleg2;
    glBindTexture(GL_TEXTURE_2D, LlegTexture);
    glTranslatef(s9->s.c[0], s9->s.c[1], 0.0f);
    glRotatef(-s9->s.rot, 0.0f, 0.0f, 1.0f);
    w = s9->s.width;
    h = s9->s.height;
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f); glVertex2i(-w, 0);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(-w, h);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(w, h);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(w, 0);
    glEnd();
    glPopMatrix();

    glPopMatrix();

    if(game->health <= 75)
    {
	//s2->s.rot += 50.0f;
	//s2->s.c[0] += 10;
	//s2->s.c[1] += -5;
    }

}

void displayAltitude(Game *game) 
{
    int i = STARTING_ALTITUDE;
    while (i > 0) {
	if ((game->altitude < (i + 400)) && (game->altitude > (i - 400))) {
	    Rect r, h;
	    char cstr[10];
	    char hp[10];
	    r.left = xres - 50;
	    r.bot = i - yres/2;
	    r.center = xres - 50;
	    r.width = 500;
	    r.height = 100;
	    sprintf (cstr, "%d", i);
	    strcat (cstr, "ft");
	    ggprint16(&r, 16, 0xdd4814, "%s", cstr);
	    h.left = 50;
	    h.bot = i - yres/2;
	    h.center = xres/2;
	    h.width = 100;
	    h.height = 50;
	    sprintf(hp, "%d", game->health);
	    ggprint16(&h, 16, 0xdd4814, "%s", hp);
	}
	i = i - 100;
    }
}

void renderStartMenu(Game *game)
{       
    Rect start;
    Rect click;

    start.bot = game->altitude - yres/4;
    start.width = 500;
    start.height = 100;
    start.center = xres/2 + yres/4;
    start.left = xres/2;

    click.bot = game->altitude - yres/2;
    click.width = 500;
    click.height = 100;
    click.center = xres/2;
    click.left = xres/2;

    ggprint16(&start, 1000, 0x00fff000, "PARASHOOT!");
    ggprint16(&click, 1000, 0x00fff000, "Click to start");
}
