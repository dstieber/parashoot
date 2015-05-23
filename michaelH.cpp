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


void InitMissileTemplate() {
    MissileTemplate = ppm6GetImage("./images/MissileTemplate.ppm");
    glGenTextures(1, &MissileTsilhouetteTexture);

    //Cloud 2
    glBindTexture(GL_TEXTURE_2D, MissileTsilhouetteTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *MissileTsilhouetteData = buildAlphaData(MissileTemplate);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, MissileTemplate->width,
	    MissileTemplate->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	    MissileTsilhouetteData);
    delete [] MissileTsilhouetteData;
}

void renderBlueMissile(Game *game) {
    int w = 40;
    int h = 84;

    if(game->altitude < 11500 && game->altitude > 10000)
    {
	Object *mv;
	Vec *m;
	m = &game->Missile.s.center;
	mv = &game->Missile;

	glBindTexture(GL_TEXTURE_2D, MissileTsilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(m->x-w, m->y-h);
	glTexCoord2f(0.0f, 0.5f); glVertex2i(m->x-w, m->y+h);
	glTexCoord2f(0.25f, 0.5f); glVertex2i(m->x+w, m->y+h);
	glTexCoord2f(0.25f, 1.0f); glVertex2i(m->x+w, m->y-h);
	glEnd();

	mv->velocity.y = 15;
    }
}

void renderRedMissile(Game *game) {
    int w = 40;
    int h = 84;

    if(game->altitude < 11500 && game->altitude > 10000)
    {
	Object *mv;
	Vec *m;
	m = &game->Missile.s.center;
	mv = &game->Missile;

	glBindTexture(GL_TEXTURE_2D, MissileTsilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.5f, 1.0f); glVertex2i(m->x-w, m->y-h);
	glTexCoord2f(0.5f, 0.5f); glVertex2i(m->x-w, m->y+h);
	glTexCoord2f(0.75f, 0.5f); glVertex2i(m->x+w, m->y+h);
	glTexCoord2f(0.75f, 1.0f); glVertex2i(m->x+w, m->y-h);
	glEnd();

	mv->velocity.y = 15;
    }
}

void renderYellowMissile(Game *game) {
    int w = 40;
    int h = 84;

    if(game->altitude < 11500 && game->altitude > 10000)
    {
	Object *mv;
	Vec *m;
	m = &game->Missile.s.center;
	mv = &game->Missile;

	glBindTexture(GL_TEXTURE_2D, MissileTsilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.5f, 0.5f); glVertex2i(m->x-w, m->y-h);
	glTexCoord2f(0.5f, 0.0f); glVertex2i(m->x-w, m->y+h);
	glTexCoord2f(0.75f, 0.0f); glVertex2i(m->x+w, m->y+h);
	glTexCoord2f(0.75f, 0.5f); glVertex2i(m->x+w, m->y-h);
	glEnd();

	mv->velocity.y = 15;
    }
}

void InitBirdTemplate() {
    BirdTemplate = ppm6GetImage("./images/BirdsTemplate2.ppm");
    glGenTextures(1, &BirdTsilhouetteTexture);

    //Cloud 2
    glBindTexture(GL_TEXTURE_2D, BirdTsilhouetteTexture);
    glPixelStorei(GL_UNPACK_ALIGNMENT,1);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    unsigned char *BirdTsilhouetteData = buildAlphaData(BirdTemplate);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, BirdTemplate->width,
	    BirdTemplate->height, 0, GL_RGBA, GL_UNSIGNED_BYTE,
	    BirdTsilhouetteData);
    delete [] BirdTsilhouetteData;
}

void renderOrangeBird(Game *game) {
    int w = 17;
    int h = 13;

    Character *ov;
    Vec *o;
    o = &game->BlueBird.s.center;
    ov = &game->BlueBird;

    glBindTexture(GL_TEXTURE_2D, BirdTsilhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.50f);   glVertex2i(o->x-w, o->y-h);
    glTexCoord2f(0.0f, 0.25f);  glVertex2i(o->x-w, o->y+h);
    glTexCoord2f(0.25f, 0.25f); glVertex2i(o->x+w, o->y+h);
    glTexCoord2f(0.25f, 0.50f);  glVertex2i(o->x+w, o->y-h);
    glEnd();
    ov->velocity.x = 9;
}

void renderRedBird(Game *game) {
    int wR = 17;
    int hR = 13;

    if (game->altitude < 11500 && game->altitude > 10000) {
    Character *rv;
    Vec *r;
    r = &game->BlueBird.s.center;
    rv = &game->BlueBird;

    glBindTexture(GL_TEXTURE_2D, BirdTsilhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.75f);   glVertex2i(r->x-wR, r->y-hR);
    glTexCoord2f(0.0f, 0.50f);  glVertex2i(r->x-wR, r->y+hR);
    glTexCoord2f(0.25f, 0.50f); glVertex2i(r->x+wR, r->y+hR);
    glTexCoord2f(0.25f, 0.75f);  glVertex2i(r->x+wR, r->y-hR);
    glEnd();
    rv->velocity.x = 9;
    }
}

void renderGreenBird(Game *game) {
    int wG = 17;
    int hG = 13;

    if (game->altitude < 11500 && game->altitude > 10000) {
    Character *gv;
    Vec *g;
    g = &game->BlueBird.s.center;
    gv = &game->BlueBird;

    glBindTexture(GL_TEXTURE_2D, BirdTsilhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 0.25f);   glVertex2i(g->x-wG, g->y-hG);
    glTexCoord2f(0.0f, 0.0f);  glVertex2i(g->x-wG, g->y+hG);
    glTexCoord2f(0.25f, 0.0f); glVertex2i(g->x+wG, g->y+hG);
    glTexCoord2f(0.25f, 0.25f);  glVertex2i(g->x+wG, g->y-hG);
    glEnd();
    gv->velocity.x = 9;
    }
}

void renderPurpleBird(Game *game) {
    int wP = 17;
    int hP = 13;

    Character *pv;
    Vec *p;
    p = &game->BlueBird.s.center;
    pv = &game->BlueBird;

    glBindTexture(GL_TEXTURE_2D, BirdTsilhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    glTexCoord2f(0.0f, 1.0f);   glVertex2i(p->x-wP, p->y-hP);
    glTexCoord2f(0.0f, 0.75f);  glVertex2i(p->x-wP, p->y+hP);
    glTexCoord2f(0.25f, 0.75f); glVertex2i(p->x+wP, p->y+hP);
    glTexCoord2f(0.25f, 1.0f);  glVertex2i(p->x+wP, p->y-hP);
    glEnd();
    pv->velocity.x = 9;
}

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

    Object *cv = &game->Cloud1;
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

    if (game->altitude < 7000) {
	cv->velocity.y = 0;

	if (c->x <= 50) {
	    cv->velocity.x = rand()%2;
	}
	if (c->x >= (xres-50)) {
	    cv->velocity.x = -rand()%2;
	}
    } else {
    	if (cv->velocity.x == 0) {
	    cv->velocity.y = .15;
	    cv->velocity.x = rand()%2;
    	}

	if (c->x <= 50) {
	    cv->velocity.x = rand()%2;
    	}
        if (c->x >= (xres-50)) {
 	    cv->velocity.x = -rand()%2;
        }
    }	
}

void MakeCloud(Game *game) {
    Object *cd;
    cd = &game->Cloud1;

    cd->s.center.x = 250;
    cd->s.center.y = (game->altitude - 750);
    cd->velocity.x = 0;
    cd->velocity.y = 0;
}

void CloudMovement(Game *game) {
    Object *cd;
    cd = &game->Cloud1;
    cd->s.center.x += cd->velocity.x;
    cd->s.center.y += cd->velocity.y;
    cd->s.center.y -= GRAVITY;
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

    Object *cv = &game->Cloud2;
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

    if (game->altitude < 7000) {
	cv->velocity.y = 0;

	if (c->x <= 50) {
	    cv->velocity.x = rand()%2;
	}
	if (c->x >= (xres-50)) {
	    cv->velocity.x = -rand()%2;
	}
    } else {
    	if (cv->velocity.x == 0) {
	    cv->velocity.y = .15;
	    cv->velocity.x = rand()%2;
    	}

	if (c->x <= 50) {
	    cv->velocity.x = rand()%2;
    	}
        if (c->x >= (xres-50)) {
 	    cv->velocity.x = -rand()%2;
        } 
    }
}

void MakeCloud2(Game *game) {
    Object *cd;
    cd = &game->Cloud2;

    cd->s.center.x = 400;
    cd->s.center.y = (game->altitude - 600);
    cd->velocity.x = 0;
    cd->velocity.y = 0;
}

void Cloud2Movement(Game *game) {
    Object *cd;
    cd = &game->Cloud2;
    cd->s.center.x += cd->velocity.x;
    cd->s.center.y += cd->velocity.y;
    cd->s.center.y -= GRAVITY;
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
    m->s.center.y = (game->altitude - yres/2);
    m->velocity.x = 0;
    m->velocity.y = 0;
}

void MountainMovement(Game *game) {
    Object *m = &game->Mountain;
    m->s.center.x += m->velocity.x;
    m->s.center.y += m->velocity.y;
    m->s.center.y -= GRAVITY;
}

void renderMountain(Game *game) {
    int w = 400;
    int h = 400;

    Vec *m = &game->Mountain.s.center;
    Object *mv = &game->Mountain;

    glBindTexture(GL_TEXTURE_2D, msilhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);

    glTexCoord2f(0.0f, 1.0f); glVertex2i(m->x-w, m->y-h -400);	//-400
    glTexCoord2f(0.0f, 0.0f); glVertex2i(m->x-w, m->y+h -400);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(m->x+w, m->y+h -400);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(m->x+w, m->y-h -400);
    glEnd();

    if (game->altitude < 7000) {
	mv->velocity.y = 0;
    } else {
	mv->velocity.y = .15;	// .25
    }
}

void InitMissile() {
    MissileImage = ppm6GetImage("./images/MissileFinished.ppm");
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
    Object *m;
    m = &game->Missile;

    m->s.center.x = 400;
    m->s.center.y = (game->altitude - (yres/2) - 600);
    m->velocity.x = 0;
    m->velocity.y = 0;
}

void MissileMovement(Game *game) {
    Object *m;
    m = &game->Missile;
    m->s.center.x += m->velocity.x;
    m->s.center.y += m->velocity.y;
    m->s.center.y -= GRAVITY;
}

void MissileRender(Game *game) {
    int w = 40;
    int h = 84;

    if(game->altitude < 11500 && game->altitude > 10000)
    {
	Object *mv;
	Vec *m;
	m = &game->Missile.s.center;
	mv = &game->Missile;

	glBindTexture(GL_TEXTURE_2D, MSsilhouetteTexture);
	glEnable(GL_ALPHA_TEST);
	glAlphaFunc(GL_GREATER, 0.0f);
	glColor4ub(255, 255, 255, 255);
	glBegin(GL_QUADS);
	glTexCoord2f(0.0f, 1.0f); glVertex2i(m->x-w, m->y-h);
	glTexCoord2f(0.0f, 0.0f); glVertex2i(m->x-w, m->y+h);
	glTexCoord2f(0.5f, 0.0f); glVertex2i(m->x+w, m->y+h);
	glTexCoord2f(0.5f, 1.0f); glVertex2i(m->x+w, m->y-h);
	glEnd();

	mv->velocity.y = 15;
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
