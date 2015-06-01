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

Ppmimage *LogoImage = NULL;
GLuint LsilhouetteTexture;

void InitBlueBird() {
	BlueBirdImage = ppm6GetImage("./images/BirdsTemplate.ppm");
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

void InitBlueBird2() {
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

void MakeBlueBird(Game *game) {
	Bird *b = new Bird;
	b->next = game->bhead;
	if (game->bhead !=NULL)
		game->bhead->prev = b;
	game->bhead = b;
	game->nbirds++;

	if (rand()%2 == 0) {
		b->s.center.x = 0;
		b->s.center.y = (game->altitude - rand()%yres);
		b->velocity.x = rand()%10 + 10;
		b->velocity.y = -GRAVITY;
	} else {
		b->s.center.x = xres;
		b->s.center.y = (game->altitude - rand()%yres);
		b->velocity.x = -rand()%10 - 10;
		b->velocity.y = -GRAVITY;
	}

}

void MakeBlueBird2(Game *game) {
	Character *b;
	b = &game->BlueBird2;

	b->s.center.x = xres/2+400;
	b->s.center.y = (game->altitude- (yres/2)+50);
	b->velocity.x = 0;
	b->velocity.y = 0;
}

void BlueBirdMovement(Game *game) {
	Bird *b = game->bhead;
	while(b)
	{
		if (b->s.center.x > xres)
		{
			deleteBlueBird(game, b);
			b = b->next;
			game->nbirds--;
		} else {
			b->s.center.x += b->velocity.x;
			b->s.center.y += b->velocity.y;
			b = b->next;
		}
	}
}

void BlueBirdMovement2(Game *game) {
	Character *b;
	b= &game->BlueBird2;
	b->s.center.x += b->velocity.x;
	b->s.center.y += b->velocity.y;
	b->s.center.y -= GRAVITY;

}

void BlueBirdRender(Game *game) {
	Bird *b = game->bhead;
	while (b) {
		int wB= 17;
		int hB= 13;

		Vec *bv = &b->s.center;

		glBindTexture(GL_TEXTURE_2D, BsilhouetteTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255, 255, 255, 255);
		glBegin(GL_QUADS);
		if (b->velocity.x > 0) {
			glTexCoord2f(0.0f, 1.0f); glVertex2i(bv->x-wB, bv->y-hB);
			glTexCoord2f(0.0f, 0.8f); glVertex2i(bv->x-wB, bv->y+hB);
			glTexCoord2f(0.25f, 0.8f); glVertex2i(bv->x+wB, bv->y+hB);
			glTexCoord2f(0.25f, 1.0f); glVertex2i(bv->x+wB, bv->y-hB);
		} else {
			glTexCoord2f(0.75f, 1.0f); glVertex2i(bv->x-wB, bv->y-hB);
			glTexCoord2f(0.75f, 0.8f); glVertex2i(bv->x-wB, bv->y+hB);
			glTexCoord2f(1.0f, 0.8f); glVertex2i(bv->x+wB, bv->y+hB);
			glTexCoord2f(1.0f, 1.0f); glVertex2i(bv->x+wB, bv->y-hB);
		}
		glEnd();
		b = b->next;
	}
}

void renderRedBird(Game *game) {
	Bird *b = game->bhead;
	while (b) {
		int wB= 17;
		int hB= 13;
		Vec *bv = &b->s.center;

		glBindTexture(GL_TEXTURE_2D, BsilhouetteTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255, 255, 255, 255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.6f); glVertex2i(bv->x-wB, bv->y-hB);
		glTexCoord2f(0.0f, 0.4f); glVertex2i(bv->x-wB, bv->y+hB);
		glTexCoord2f(0.25f, 0.4f); glVertex2i(bv->x+wB, bv->y+hB);
		glTexCoord2f(0.25f, 0.6f); glVertex2i(bv->x+wB, bv->y-hB);
		glEnd();
		b = b->next;
	}
}

void BlueBirdRender2(Game *game) {
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
	// Different parameter for different sound
	// Ex) fmod_playsound(0) plays the first sound (the song)
	if(fmod_createsound((char *)"./sounds/Highly_Suspicious.mp3", 0)) {
		printf("ERROR");
		return;
	}
	if(fmod_createsound((char *)"./sounds/bird.mp3", 1)) {
		printf("ERROR for bird sound");
		return;
	}
	if(fmod_createsound((char *)"./sounds/missile.mp3", 2)) {
		printf("Error for missile sound");
		return;
	}
	if(fmod_createsound((char *)"./sounds/missile_whistle.mp3", 3)) {
		printf("Error for missile whistle");
		return;
	}
	if(fmod_createsound((char *)"./sounds/generic_collision.mp3", 4)) {
		printf("Error for collision sound");
		return;
	}
	if(fmod_createsound((char *)"./sounds/missile_loud.mp3", 5)) {
		printf("Error for loud missile");
		return;
	}
	if(fmod_createsound((char *)"./sounds/wind_soft.wav", 6)) {
		printf("Wind sound");
	}
	if(fmod_createsound((char *)"./sounds/lose.mp3", 7)) {
		printf("Lose sound");
		return;
	}
	if(fmod_createsound((char *)"./sounds/win.mp3", 8)) {
		printf("wind sound");
		return;
	}
	fmod_setmode(0, FMOD_LOOP_NORMAL);  //FMOD_LOOP_NORMAL/OFF

/*
	fmod_setmode(1, FMOD_LOOP_NORMAL);
	fmod_setmode(2, FMOD_LOOP_NORMAL);
	fmod_setmode(3, FMOD_LOOP_NORMAL);
	fmod_setmode(4, FMOD_LOOP_NORMAL);
	fmod_setmode(5, FMOD_LOOP_NORMAL);
	fmod_setmode(6, FMOD_LOOP_NORMAL);
	fmod_setmode(7, FMOD_LOOP_NORMAL);
	fmod_setmode(8, FMOD_LOOP_NORMAL);

*/
#endif
}

void play() {
	fmod_playsound(0);

}
void playSoundEffects() {
//**********************************************************************************************
//Needs to be some random function here!!
/*
	if(rand()%10 == 17)
	{
	fmod_playsound(1);
	}
*/


}
void InitLogo() {
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

void MakeLogo(Game *game) {
	Object *l;

	l = &game->Logo;
	l->s.center.x = xres/2+2;
	l->s.center.y = (game->altitude - (yres/2)+150);

}

void displayHealth(Game *game) {
	int i = game->health;
	Rect r;
	char cstr[10];
	r.left = 50;
	r.bot = game->altitude - 50;
	r.center = xres - 50;
	r.width = 500;
	r.height = 100;
	sprintf(cstr, "%d", i);
	strcat(cstr, " HP");
	if (game->health >= 75) {
		ggprint16(&r, 1000, 0x04B404, "%s", cstr);
	}
	if (game->health >= 50 && game->health < 75) {
		ggprint16(&r, 1000, 0xFFFF00, "%s", cstr);
	}
	if (game->health >= 25 && game->health < 50) {
		ggprint16(&r, 1000, 0xFF8000, "%s", cstr);
	}
	if (game->health < 25) {
		ggprint16(&r, 1000, 0x8A0808, "%s", cstr);
	}
	if (game->health <= 0) {
		ggprint16(&r, 1000, 0x000000, "%s", cstr);
	}
}

void LogoRender(Game *game) {
	int w= 350;
	int h= 80;

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
