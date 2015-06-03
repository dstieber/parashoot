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
GLuint RarmsilhouetteTexture;
GLuint LarmsilhouetteTexture;
GLuint RlegsilhouetteTexture;
GLuint LlegsilhouetteTexture;
GLuint HeadsilhouetteTexture;
GLuint RarmTexture;
GLuint BodyTexture;
GLuint LarmTexture;
GLuint RlegTexture;
GLuint LlegTexture;
GLuint LimbTexture;
GLuint HeadTexture;

void initSky(void) 
{
	skyImage = ppm6GetImage("./images/Sky.ppm");
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
	//body Texture
	BodyImage = ppm6GetImage("./images/Body.ppm");
	glGenTextures(1, &silhouetteTexture);
	glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *silhouetteData = buildAlphaData(BodyImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BodyImage->width,
			BodyImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
	delete [] silhouetteData;

	//head
	HeadImage = ppm6GetImage("./images/Head.ppm");
	glGenTextures(1, &HeadsilhouetteTexture);
	glBindTexture(GL_TEXTURE_2D, HeadsilhouetteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *HeadsilhouetteData = buildAlphaData(HeadImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, HeadImage->width, 
			HeadImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, HeadsilhouetteData);
	delete [] HeadsilhouetteData;

	//Right arm
	RarmImage = ppm6GetImage("./images/Arm1.ppm");
	glGenTextures(1, &RarmsilhouetteTexture);
	glBindTexture(GL_TEXTURE_2D, RarmsilhouetteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *RarmsilhouetteData = buildAlphaData(RarmImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RarmImage->width, 
			RarmImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, RarmsilhouetteData);
	delete [] RarmsilhouetteData;

	//Left arm
	LarmImage = ppm6GetImage("./images/Larm1.ppm");
	glGenTextures(1, &LarmsilhouetteTexture);
	glBindTexture(GL_TEXTURE_2D, LarmsilhouetteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *LarmsilhouetteData = buildAlphaData(LarmImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, LarmImage->width, 
			LarmImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LarmsilhouetteData);
	delete [] LarmsilhouetteData;

	//Right leg
	RlegImage = ppm6GetImage("./images/Rleg.ppm");
	glGenTextures(1, &RlegsilhouetteTexture);
	glBindTexture(GL_TEXTURE_2D, RlegsilhouetteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *RlegsilhouetteData = buildAlphaData(RlegImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, RlegImage->width, 
			RlegImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, RlegsilhouetteData);
	delete [] RlegsilhouetteData;

	//Left leg
	LlegImage = ppm6GetImage("./images/Lleg.ppm");
	glGenTextures(1, &LlegsilhouetteTexture);
	glBindTexture(GL_TEXTURE_2D, LlegsilhouetteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *LlegsilhouetteData = buildAlphaData(LlegImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, LlegImage->width, 
			LlegImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LlegsilhouetteData);
	delete [] LlegsilhouetteData;

	//Limbs
	LimbImage = ppm6GetImage("./images/Limb.ppm");
	glGenTextures(1, &LimbTexture);
	glBindTexture(GL_TEXTURE_2D, LimbTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *LimbData = buildAlphaData(LimbImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, LimbImage->width, 
			LimbImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, LimbData);

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
	glBindTexture(GL_TEXTURE_2D, HeadsilhouetteTexture);
	glTranslatef(s->s.c[0], s->s.c[1], 0.0f);
	glRotatef(-s->s.rot, 0.0f, 0.0f, 1.0f);
	glColor4ub(255,255,255,255);
	w = s->s.width;
	h = s->s.height;
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2f(-(float)w, h);
	glTexCoord2f(0.0f, 0.0f); glVertex2f(-(float)w, h+40);
	glTexCoord2f(0.5f, 0.0f); glVertex2f( (float)w, h+40);
	glTexCoord2f(0.5f, 1.0f); glVertex2f( (float)w, h);
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
	glBindTexture(GL_TEXTURE_2D, RarmsilhouetteTexture);
	Character *s3 = &game->rarm2;
	glTranslatef(s3->s.c[0], s3->s.c[1], 0.0f);
	glRotatef(-s3->s.rot, 0.0f, 0.0f, 1.0f);
	glColor4ub(255,255,255,255);
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
	glBindTexture(GL_TEXTURE_2D, LarmsilhouetteTexture);
	glTranslatef(s5->s.c[0], s5->s.c[1], 0.0f);
	glRotatef(-s5->s.rot, 0.0f, 0.0f, 1.0f);
	glColor4ub(255,255,255,255);
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
	glBindTexture(GL_TEXTURE_2D, RlegsilhouetteTexture);
	glTranslatef(s7->s.c[0], s7->s.c[1], 0.0f);
	glRotatef(-s7->s.rot, 0.0f, 0.0f, 1.0f);
	glColor4ub(255,255,255,255);
	w = s7->s.width;
	h = s7->s.height;
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(-w, h);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(w, h);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(w, 0);
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
	glBindTexture(GL_TEXTURE_2D, LlegsilhouetteTexture);
	glTranslatef(s9->s.c[0], s9->s.c[1], 0.0f);
	glRotatef(-s9->s.rot, 0.0f, 0.0f, 1.0f);
	glColor4ub(255,255,255,255);
	w = s9->s.width;
	h = s9->s.height;
	glBegin(GL_QUADS);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(-w, 0);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(-w, h);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(w, h);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(w, 0);
	glEnd();
	glPopMatrix();

	glPopMatrix();

}

void displayAltitude(Game *game) 
{
	int i = STARTING_ALTITUDE;
	while (i > 0) {
		if ((game->altitude < (i + yres/2)) && (game->altitude > (i - yres/2))) {
			Rect r;
			char cstr[10];
			r.left = xres - 50;
			r.bot = i - yres/2;
			r.center = xres - 50;
			r.width = 500;
			r.height = 100;
			sprintf (cstr, "%d", i);
			strcat (cstr, "ft");
			ggprint16(&r, 16, 0xdd4814, "%s", cstr);
		}
		i = i - 100;
	}
}

void renderStartMenu(Game *game)
{  
	InitLogo();
	MakeLogo(game);
	LogoRender(game);

	Rect click;
	click.bot = game->altitude - yres/2;
	click.width = 500;
	click.height = 100;
	click.center = xres/2;
	click.left = xres/2;
	ggprint16(&click, 16, 0xffffff, "Click to start");
}

void renderGameOver(void)
{
	Rect gameOver;
	gameOver.bot = yres/2;
	gameOver.width = 500;
	gameOver.height = 100;
	gameOver.center = xres/2;
	gameOver.left = xres/2;
	ggprint16(&gameOver, 16, 0xdd4814, "Game Over!");
}

void randomGenerator(Game *game) 
{
	srand (time(NULL));

	if (rand()%10 < 9) 
	{
		MakeBlueBird(game);
		BlueBirdRender(game);
	}

}

void deleteBlueBird(Game *game, Bird *node)
{
	if (game->bhead != NULL) {
		if (node->prev == NULL) {
			if (node->next == NULL) {
				game->bhead = NULL;
			} else {
				node->next->prev = NULL;
				game->bhead = node->next;
			}
		} else {
			if (node->next == NULL) {
				node->prev->next = NULL;
			} else {
				node->prev->next = node->next;
				node->next->prev = node->prev;
			}
		}
		delete node;
		node = NULL;
	}
}

void deleteMissile(Game *game, Missile *node)
{
	if (game->mhead != NULL) {
		if (node->prev == NULL) {
			if (node->next == NULL) {
				game->mhead = NULL;
			} else {
				node->next->prev = NULL;
				game->mhead = node->next;
			}
		} else {
			if (node->next == NULL) {
				node->prev->next = NULL;
			} else {
				node->prev->next = node->next;
				node->next->prev = node->prev;
			}
		}
		delete node;
		node = NULL;
	}
}
