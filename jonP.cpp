// Jonathan Popkin
#include "jonP.h"

Ppmimage *BlueBirdImage = NULL;
GLuint BsilhouetteTexture;

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
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255, 255, 255, 255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 1.0f); glVertex2i(b->x-wB, b->y-hB);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(b->x-wB, b->y+hB);
		glTexCoord2f(0.5f, 0.0f); glVertex2i(b->x+wB, b->y+hB);
		glTexCoord2f(0.5f, 1.0f); glVertex2i(b->x+wB, b->y-hB);
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
	fmod_playsound(0);
}
