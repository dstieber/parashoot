/* Program : Homework 3 / Lab6
 * Author  : Michael Harp
 * Purpose : Render mountain, initialize keys, check keys functions
 */

#include "michaelH.h"

Ppmimage *MissileImage = NULL;
GLuint MSsilhouetteTexture;

Ppmimage *mountainImage = NULL;
GLuint msilhouetteTexture;

Ppmimage *Cloud2Image = NULL;
GLuint CsilhouetteTexture;

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
    Character *cd;
    cd = &game->Cloud2;

    cd->s.center.x = 400;
    cd->s.center.y = (game->altitude - 200);
    cd->velocity.x = 0;
    cd->velocity.y = 0;
}

void Cloud2Movement(Game *game) {
	Character *cd;
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

void renderMountain(Game *game) {
    glBindTexture(GL_TEXTURE_2D, msilhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    int ybottom = game->altitude - yres;	
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, ybottom);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, game->altitude);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, game->altitude);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, ybottom);
    glEnd();
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
    
    Character *m;
    m = &game->Missile;

    m->s.center.x = 400;
    m->s.center.y = (game->altitude - (yres/2) - 600);
    m->velocity.x = 0;
    m->velocity.y = 0;
}

void MissileMovement(Game *game) {
	Character *m;
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
	Character *mv;
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
