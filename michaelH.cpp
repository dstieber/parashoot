/* Program : Homework 3 / Lab6
 * Author  : Michael Harp
 * Purpose : Render mountain, initialize keys, check keys functions
 */

#include "michaelH.h"

Ppmimage *MissileImage = NULL;
GLuint MSsilhouetteTexture;

Ppmimage *mountainImage = NULL;
GLuint msilhouetteTexture;

Ppmimage *CloudImage = NULL;
GLuint C1silhouetteTexture;

Ppmimage *Cloud2Image = NULL;
GLuint CsilhouetteTexture;

Ppmimage *PlaneImage = NULL;
GLuint PsilhouetteTexture;

Ppmimage *BirdTemplate = NULL;
GLuint BirdTsilhouetteTexture;

Ppmimage *MissileTemplate = NULL;
GLuint MissileTsilhouetteTexture;

void InitCloud() {
	CloudImage = ppm6GetImage("./images/Cloud1.ppm");
	glGenTextures(1, &C1silhouetteTexture);

	//Cloud 2
	glBindTexture(GL_TEXTURE_2D, C1silhouetteTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *C1silhouetteData = buildAlphaData(CloudImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, CloudImage->width,
			CloudImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			C1silhouetteData);
	delete [] C1silhouetteData;
}

void renderCloud(Game *game) {

	int w = 120;  //565
	int h = 60;  //332 

	Vec *c = &game->Cloud1.s.center;

	glBindTexture(GL_TEXTURE_2D, C1silhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(c->x-w, c->y-h);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(c->x-w, c->y+h);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(c->x+w, c->y+h);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(c->x+w, c->y-h);
	glEnd();
}

void MakeCloud(Game *game) {
	Object *cd;
	cd = &game->Cloud1;

	cd->s.center.x = xres/4;
	cd->s.center.y = (game->altitude - (yres/2) + yres/10);
	cd->velocity.x = rand()%2 + 1;
	cd->velocity.y = -GRAVITY;
}

void CloudMovement(Game *game) {
	Object *cd;
	cd = &game->Cloud1;

	if (cd->s.center.x <= 50) {
		cd->velocity.x = rand()%2;
	}
	if (cd->s.center.x >= (xres-50)) {
		cd->velocity.x = -rand()%2;
	}
	if (game->altitude < 500) {
		cd->velocity.y = -GRAVITY;
	}

	cd->s.center.x += cd->velocity.x;
	cd->s.center.y += cd->velocity.y;
}


void InitCloud2() {
	Cloud2Image = ppm6GetImage("./images/Cloud2.ppm");
	glGenTextures(1, &CsilhouetteTexture);

	//Cloud 2
	glBindTexture(GL_TEXTURE_2D, CsilhouetteTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *CsilhouetteData = buildAlphaData(Cloud2Image);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, Cloud2Image->width,
			Cloud2Image->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			CsilhouetteData);
	delete [] CsilhouetteData;
}

#define rnd() (float)rand()/(float)RAND_MAX
void renderCloud2(Game *game) {
	int w = 120;  //482
	int h = 60;  //222 

	Vec *c = &game->Cloud2.s.center;    

	glBindTexture(GL_TEXTURE_2D, CsilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(c->x-w, c->y-h);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(c->x-w, c->y+h);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(c->x+w, c->y+h);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(c->x+w, c->y-h);
	glEnd();
}

void MakeCloud2(Game *game) {
	Object *cd;
	cd = &game->Cloud2;

	cd->s.center.x = xres/2;
	cd->s.center.y = (game->altitude - (yres/2 + yres/20));
	cd->velocity.x = -(rand()%2 + 1);
	cd->velocity.y = -GRAVITY;
}

void Cloud2Movement(Game *game) {
	Object *cd;
	cd = &game->Cloud2;

	if (cd->s.center.x <= 50) {
		cd->velocity.x = rand()%2;
	}
	if (cd->s.center.x >= (xres-50)) {
		cd->velocity.x = -rand()%2;
	}
	if (game->altitude < 500) {
		cd->velocity.y = -GRAVITY;
	}

	cd->s.center.x += cd->velocity.x;
	cd->s.center.y += cd->velocity.y;
}

void InitMountain() {
	mountainImage = ppm6GetImage("./images/Background_Mount.ppm");
	glGenTextures(1, &msilhouetteTexture);

	//Mountain
	glBindTexture(GL_TEXTURE_2D, msilhouetteTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *msilhouetteData = buildAlphaData(mountainImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mountainImage->width,
			mountainImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			msilhouetteData);
	delete [] msilhouetteData;
}

void MakeMountain(Game *game) {
	Object *m = &game->Mountain;

	m->s.center.x = xres/2;
	m->s.center.y = (game->altitude - yres*0.875);
	m->velocity.x = 0;
	m->velocity.y = -GRAVITY + (float)yres/5333;
}

void MountainMovement(Game *game) {
	Object *m = &game->Mountain;
	if (game->altitude < 500)
		m->velocity.y = -GRAVITY;
	m->s.center.y += m->velocity.y;
}

void renderMountain(Game *game) {
	int h = yres/2;

	Vec *m = &game->Mountain.s.center;

	glBindTexture(GL_TEXTURE_2D, msilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	
	glTexCoord2f(0.0f, 1.0f); glVertex2i(0, m->y-h - yres/2);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(0, m->y+h - yres/2);
	glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, m->y+h - yres/2);
	glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, m->y-h - yres/2);
	
	glEnd();
}

void InitMissile() {
	MissileImage = ppm6GetImage("./images/MissileTemplate.ppm");
	glGenTextures(1, &MSsilhouetteTexture);

	//Missile
	glBindTexture(GL_TEXTURE_2D, MSsilhouetteTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *MSsilhouetteData = buildAlphaData(MissileImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MissileImage->width,
			MissileImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			MSsilhouetteData);
	delete [] MSsilhouetteData;
}

void MakeMissile(Game *game) {
	Missile *m = new Missile;
	m->next = game->mhead;
	if (game->mhead != NULL)
		game->mhead->prev = m;
	game->mhead = m;
	game->nmissiles++;

	m->s.center.x = rand()%xres;
	m->s.center.y = (game->altitude - yres - 84);
	m->velocity.x = 0;
	m->velocity.y = 15;
}

void MissileMovement(Game *game) 
{
	Missile *m = game->mhead;
	while(m)
	{
		if(m->s.center.y > game->altitude + (yres/2))
		{
			deleteMissile(game, m);
			m = m->next;
			game->nmissiles--;
		} else {
			m->s.center.x += m->velocity.x;
			m->s.center.y += m->velocity.y;
			m = m->next;
		}
	}
}

void MissileRender(Game *game) 
{
	Missile *m = game->mhead;
	while (m) {
		int w = 40;
		int h = 84;

		Vec *mv = &m->s.center;

		glBindTexture(GL_TEXTURE_2D, MSsilhouetteTexture);
		glEnable(GL_ALPHA_TEST);
		glAlphaFunc(GL_GREATER, 0.0f);
		glColor4ub(255, 255, 255, 255);
		glBegin(GL_QUADS);
		glTexCoord2f(0.0f, 0.5f); glVertex2i(mv->x-w, mv->y-h);
		glTexCoord2f(0.0f, 0.0f); glVertex2i(mv->x-w, mv->y+h);
		glTexCoord2f(0.25f, 0.0f); glVertex2i(mv->x+w, mv->y+h);
		glTexCoord2f(0.25f, 0.5f); glVertex2i(mv->x+w, mv->y-h);
		glEnd();
		m = m->next;
	}
}

void InitPlane() {
	PlaneImage = ppm6GetImage("./images/PlaneTemplate.ppm");
	glGenTextures(1, &PsilhouetteTexture);

	//Plane
	glBindTexture(GL_TEXTURE_2D, PsilhouetteTexture);
	glPixelStorei(GL_UNPACK_ALIGNMENT,1);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *PsilhouetteData = buildAlphaData(PlaneImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, PlaneImage->width,
			PlaneImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
			PsilhouetteData);
	delete [] PsilhouetteData;
}

void MakePlane(Game *game) {
	Object *p;
	p = &game->Plane;

	p->s.center.x = 400;
	p->s.center.y = (game->altitude - 400);
	p->velocity.x = 0;
	p->velocity.y = 0;
}

void PlaneMovement(Game *game) {
	Object *p;
	p = &game->Plane;
	p->s.center.x += p->velocity.x;
	p->s.center.y += p->velocity.y;
	p->s.center.y -= GRAVITY;
}

void renderPlane(Game *game) {
	int w = 150;		//646   //646
	int h = 75;		//632   //316

	//Object *pv;
	Vec *p;
	p = &game->Plane.s.center;
	//pv = &game->Plane;

	glBindTexture(GL_TEXTURE_2D, PsilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);

	/*		// Right view of plane
			glTexCoord2f(0.0f, 1.0f); glVertex2i(p->x-w, p->y-h);  
			glTexCoord2f(0.0f, 0.5f); glVertex2i(p->x-w, p->y+h);  
			glTexCoord2f(1.0f, 0.5f); glVertex2i(p->x+w, p->y+h);  
			glTexCoord2f(1.0f, 1.0f); glVertex2i(p->x+w, p->y-h);  
			*/
	// Left view of plane
	glTexCoord2f(0.0f, 0.5f); glVertex2i(p->x-w, p->y-h);  
	glTexCoord2f(0.0f, 0.0f); glVertex2i(p->x-w, p->y+h);  
	glTexCoord2f(1.0f, 0.0f); glVertex2i(p->x+w, p->y+h);  
	glTexCoord2f(1.0f, 0.5f); glVertex2i(p->x+w, p->y-h);  


	glEnd();
}

void init_keys() {
	memset(keys, 0, 65536);
}

int check_keys(XEvent *e) {
	//keyboard input?
	static int shift=0;
	int key = XLookupKeysym(&e->xkey, 0);
	//Log("key: %i\n", key);
	if (e->type == KeyRelease) {
		keys[key]=0;
		if (key == XK_Shift_L || key == XK_Shift_R)
			shift=0;
		return 0;
	}
	if (e->type == KeyPress) {
		keys[key]=1;
		if (key == XK_Shift_L || key == XK_Shift_R) {
			shift=1;
			return 0;
		}
	} else {
		return 0;
	}
	if (shift){}
	switch(key) {
		case XK_Escape:
			return 1;
		case XK_f:
			break;
		case XK_s:
			break;
		case XK_Down:
			break;
		case XK_equal:
			break;
		case XK_minus:
			break;
	}
	return 0;
}
