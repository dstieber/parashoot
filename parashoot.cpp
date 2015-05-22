#include "parashoot.h"
#include "alexA.h"

int main(void)
{
    int done=0;
    srand(time(NULL));
    initXWindows();
    init_opengl(&game);
    DefineRagdoll(&game);
    create_sounds();
    play();
    init_keys();
    clock_gettime(CLOCK_REALTIME, &timePause);
    clock_gettime(CLOCK_REALTIME, &timeStart);

    //start animation
    while(!done) {
        while(XPending(dpy)) {
            //XEvent e;
            XNextEvent(dpy, &e);
            check_mouse(&e, &game);
            check_resize(&game, &e);
            done = check_keys(&e);
        }
        clock_gettime(CLOCK_REALTIME, &timeCurrent);
        timeSpan = timeDiff(&timeStart, &timeCurrent);
        timeCopy(&timeStart, &timeCurrent);
        physicsCountdown += timeSpan;
        while(physicsCountdown >= physicsRate) {
            movement(&game);
            physicsCountdown -= physicsRate;
        }
        render(&game);
        glXSwapBuffers(dpy, win);
    }
    cleanupXWindows();
    cleanup_fonts();
    return 0;
}

void set_title(void)
{
	//Set the window title bar.
	XMapWindow(dpy, win);
	XStoreName(dpy, win, "ParaShoot!");
}

void cleanupXWindows(void) {
	//do not change
	XDestroyWindow(dpy, win);
	XCloseDisplay(dpy);
}

void setup_screen_res(const int w, const int h)
{
	xres=w;
	yres=h;
}

void initXWindows(void) {
	//do not change
	GLint att[] = { GLX_RGBA, GLX_DEPTH_SIZE, 24, GLX_DOUBLEBUFFER, None };
	int w=WINDOW_WIDTH, h=WINDOW_HEIGHT;
	dpy = XOpenDisplay(NULL);
	if (dpy == NULL) {  
		std::cout << "\n\tcannot connect to X server\n" << std::endl;
		exit(EXIT_FAILURE);
	}
	Window root = DefaultRootWindow(dpy);
	XVisualInfo *vi = glXChooseVisual(dpy, 0, att);
	if(vi == NULL) {
		std::cout << "\n\tno appropriate visual found\n" << std::endl;
		exit(EXIT_FAILURE);
	}
	Colormap cmap = XCreateColormap(dpy, root, vi->visual, AllocNone);
	XSetWindowAttributes swa;
	swa.colormap = cmap;
	swa.event_mask = ExposureMask | KeyPressMask | KeyReleaseMask |
		ButtonPress | ButtonReleaseMask |
		PointerMotionMask |
		StructureNotifyMask | SubstructureNotifyMask;
	win = XCreateWindow(dpy, root, 0, 0, w, h, 0, vi->depth,
			InputOutput, vi->visual, CWColormap | CWEventMask, &swa);
	set_title();
	glc = glXCreateContext(dpy, vi, NULL, GL_TRUE);
	glXMakeCurrent(dpy, win, glc);
}



void reshape_window(Game *game, int width, int height)
{
	Character *p = &game->character;
	size_flag = true;
	setup_screen_res(width, height);
	p->s.c[0] = width/2;
	p->s.c[1] = (game->altitude - height) / 2;
	glViewport(0,0, (GLint)width, (GLint)height);
	glMatrixMode(GL_PROJECTION); glLoadIdentity();
	glMatrixMode(GL_MODELVIEW); glLoadIdentity();
	glOrtho(0, width, (game->altitude - height), game->altitude, -1, 1);
	set_title();
}


unsigned char *buildAlphaData(Ppmimage *img)
{
	//add 4th component to RGB stream...
	int a,b,c;
	unsigned char *newdata, *ptr;
	unsigned char *data = (unsigned char *)img->data;
	//newdata = (unsigned char *)malloc(img->width * img->height * 4);
	newdata = new unsigned char[img->width * img->height * 4];
	ptr = newdata;
	for (int i=0; i<img->width * img->height * 3; i+=3) {
		a = *(data+0);
		b = *(data+1);
		c = *(data+2);
		*(ptr+0) = a;
		*(ptr+1) = b;
		*(ptr+2) = c;
		//
		//new code, suggested by Chris Smith, Fall 2013
		*(ptr+3) = (a|b|c);
		//
		ptr += 4;
		data += 3;
	}
	return newdata;
}

void init_opengl(Game *game) 
{
	//OpenGL initialization
	glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);
	//Initialize matrices
	glMatrixMode(GL_PROJECTION); 
	glLoadIdentity();
	//Set 2D mode (no perspective)
	glOrtho(0, WINDOW_WIDTH, (game->altitude - WINDOW_HEIGHT), 
			game->altitude, -1, 1);
	//glOrtho(0, WINDOW_WIDTH, 0, WINDOW_HEIGHT, -1, 1);
	glMatrixMode(GL_MODELVIEW); 
	glLoadIdentity();
	//glDisable(GL_LIGHTING);
	//glDisable(GL_DEPTH_TEST);
	//glDisable(GL_FOG);
	//glDisable(GL_CULL_FACE);

	//Save the default modelview matrix
	glPushMatrix();
	//Set the screen background color
	//glClearColor(0.1, 0.5, 1.0, 1.0);
	glClearColor(0.f, 0.f, 0.f, 1.f);
	glEnable(GL_TEXTURE_2D);
	initialize_fonts();
	//
	//load the images file into a ppm structure
	//
	initSky();
	initCharacter();
	mountainImage = ppm6GetImage("./images/Background_Mount.ppm");
	InitBlueBird();
	InitBlueBird2();
    InitMissile();
    //create opengl texture elements

	//Mountain
	glBindTexture(GL_TEXTURE_2D, mountainTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexImage2D(GL_TEXTURE_2D, 0, 3, mountainImage->width,
    mountainImage->height,0, GL_RGB, GL_UNSIGNED_BYTE, mountainImage->data);  

	//
	//mountain silhouette
	glBindTexture(GL_TEXTURE_2D, msilhouetteTexture);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	unsigned char *silhouetteData2 = buildAlphaData(mountainImage);
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mountainImage->width,
			mountainImage->height, 0, GL_RGBA, 
            GL_UNSIGNED_BYTE, silhouetteData2);
	delete [] silhouetteData2;

}

void check_resize(Game *game, XEvent *e)
{
	if(e->type != ConfigureNotify)
		return;

	XConfigureEvent xce = e->xconfigure;
	if(xce.width != xres || xce.height != yres) {
		reshape_window(game, xce.width, xce.height);
	}
}

void makeCharacter(Game *game)
{
    Character *p = &game->body;
    p->s.c[0] = xres/2;
    p->s.c[1] = (game->altitude - (yres/2));
    p->velocity.y = 0;
    p->velocity.x = 0;
    game->n++;
    start_flag = false;
	MakeBlueBird(game);
	MakeBlueBird2(game);
	MakeMissile(game);
}

void check_mouse(XEvent *e, Game *game)
{
	static int savex = 0;
	static int savey = 0;
	static int n = 0;

	if (e->type == ButtonRelease) {
		return;
	}
	if (e->type == ButtonPress) {
		if (e->xbutton.button==1) {
			//Left button was pressed
			if(start_flag)
				makeCharacter(game);
			return;
		}
		if (e->xbutton.button==3) {
			//Right button was pressed
			return;
		}
	}
	//Did the mouse move?
	if (savex != e->xbutton.x || savey != e->xbutton.y) {
		savex = e->xbutton.x;
		savey = e->xbutton.y;
		if (++n < 10)
			return;
	}
}

void movement(Game *game)
{
    Character *p;
    Character *mis = &game->Missile;
    Character *b = &game->BlueBird;
    Character *b2 = &game->BlueBird2;
    if (game->n <= 0)
        return;

    p = &game->body;
    p->s.c[0] += p->s.velocityx;
    p->s.c[1] += p->s.velocityy;
    p->s.c[1] -= GRAVITY;
    game->altitude -= GRAVITY;
    gCameraY += (float)GRAVITY;
    BlueBirdMovement(game);
    BlueBirdMovement2(game);
    MissileMovement(game);
    //check for collision with objects here...
    //Shape *s;
    if (keys[XK_Right]) {
        p->s.velocityx += 2;
	game->rarm1.s.rotInc += GRAVITY/8;
	game->larm1.s.rotInc += -GRAVITY/8;
	game->rleg1.s.rotInc += GRAVITY/8;
	game->lleg1.s.rotInc += GRAVITY/8;

	game->rarm2.s.rotInc += -GRAVITY/16;
	game->larm2.s.rotInc += -GRAVITY/16;
	game->rleg2.s.rotInc += GRAVITY/16;
	game->lleg2.s.rotInc += -GRAVITY/16;
    }
    if (keys[XK_Left]) {
        p->s.velocityx += -2;
	game->rarm1.s.rotInc += -GRAVITY/8;
	game->larm1.s.rotInc += GRAVITY/8;
	game->rleg1.s.rotInc += -GRAVITY/8;
	game->lleg1.s.rotInc += -GRAVITY/8;

	game->rarm2.s.rotInc += GRAVITY/16;
	game->larm2.s.rotInc += GRAVITY/16;
	game->rleg2.s.rotInc += -GRAVITY/16;
	game->lleg2.s.rotInc += GRAVITY/16;

    }
    if (keys[XK_Up]) {
        p->s.velocityy += 2;
	game->rarm1.s.rotInc += GRAVITY/8;
	game->larm1.s.rotInc += -GRAVITY/8;
	game->rleg1.s.rotInc += GRAVITY/8;
	game->lleg1.s.rotInc += -GRAVITY/8;

	game->rarm2.s.rotInc += GRAVITY/16;
	game->larm2.s.rotInc += -GRAVITY/16;
	game->rleg2.s.rotInc += -GRAVITY/16;
	game->lleg2.s.rotInc += GRAVITY/16;
    }
    if (keys[XK_Down]) {
        p->s.velocityy -= 2;
	game->rarm1.s.rotInc += -GRAVITY/4;
	game->larm1.s.rotInc += GRAVITY/4;
	game->rleg1.s.rotInc += GRAVITY/4;
	game->lleg1.s.rotInc += GRAVITY/4;

	game->rarm2.s.rotInc += GRAVITY/8;
	game->larm2.s.rotInc += -GRAVITY/8;
	game->rleg2.s.rotInc += GRAVITY/8;
	game->lleg2.s.rotInc += -GRAVITY/8;
    }
    if(p->s.velocityy < 0)
{
	game->rarm1.s.rotInc += -GRAVITY/32;
	game->larm1.s.rotInc += GRAVITY/32;
	game->rleg1.s.rotInc += GRAVITY/32;
	game->lleg1.s.rotInc += GRAVITY/32;

	game->rarm2.s.rotInc += GRAVITY/8;
	game->larm2.s.rotInc += -GRAVITY/8;
	game->rleg2.s.rotInc += GRAVITY/8;
	game->lleg2.s.rotInc += -GRAVITY/8;
}
    if(p->s.velocityy > 0)
{
	game->rarm1.s.rotInc += GRAVITY/32;
	game->larm1.s.rotInc += -GRAVITY/32;
	game->rleg1.s.rotInc += -GRAVITY/32;
	game->lleg1.s.rotInc += -GRAVITY/32;

	game->rarm2.s.rotInc += -GRAVITY/8;
	game->larm2.s.rotInc += GRAVITY/8;
	game->rleg2.s.rotInc += -GRAVITY/8;
	game->lleg2.s.rotInc += GRAVITY/8;
}
	
	//right arm restriction
	if(game->rarm1.s.rot > 151)
	{
		game->rarm1.s.rot = 150;
	}
	if(game->rarm1.s.rot < 19)
	{
		game->rarm1.s.rot = 20;
	}

	if(game->rarm2.s.rot < 289)
	{
		game->rarm2.s.rot = 290;
	}
	if(game->rarm2.s.rot > 361)
	{
		game->rarm2.s.rot = 360;
	}
	//left arm restriction
	if(game->larm1.s.rot > 311)
	{
		game->larm1.s.rot = 310;
	}
	if(game->larm1.s.rot < 189)
	{
		game->larm1.s.rot = 190;
	}

	if(game->larm2.s.rot < -1)
	{
		game->larm2.s.rot = 0;
	}
	if(game->larm2.s.rot > 56)
	{
		game->larm2.s.rot = 55;
	} 
	//right leg restriction
	if(game->rleg1.s.rot > 161)
	{
		game->rleg1.s.rot = 160;
	}
	if(game->rleg1.s.rot < 119)
	{
		game->rleg1.s.rot = 120;
	}
	if(game->rleg2.s.rot < 9)
	{
		game->rleg2.s.rot = 10;
	}
	if(game->rleg2.s.rot > 61)
	{
		game->rleg2.s.rot = 60;
	}
	//left leg restriction
	if(game->lleg1.s.rot < 180)
	{
		game->lleg1.s.rot = 181;
	}
	if(game->lleg1.s.rot > 220)
	{
		game->lleg1.s.rot = 219;
	}
	if(game->lleg2.s.rot > 1)
	{
		game->lleg2.s.rot = 0;
	}
	if(game->lleg2.s.rot < -51)
	{
		game->lleg2.s.rot = -50;
	}

	game->rarm1.s.rot += game->rarm1.s.rotInc;
	game->larm1.s.rot += game->larm1.s.rotInc;
	game->rleg1.s.rot += game->rleg1.s.rotInc;
	game->lleg1.s.rot += game->lleg1.s.rotInc;

	game->rarm2.s.rot += game->rarm2.s.rotInc;
	game->larm2.s.rot += game->larm2.s.rotInc;
	game->rleg2.s.rot += game->rleg2.s.rotInc;
	game->lleg2.s.rot += game->lleg2.s.rotInc;

	const Flt d2r = 1.0/360*3.14159265*2.0; //degrees to radians
	yy_transform(game->rleg1.s.rotInc*d2r, game->rleg1.s.m);
	yy_transform(game->lleg1.s.rotInc*d2r, game->lleg1.s.m);
	yy_transform(game->rarm1.s.rotInc*d2r, game->rarm1.s.m);
	yy_transform(game->larm1.s.rotInc*d2r, game->larm1.s.m);

    //border collision detection
    //
    if (p->s.c[0] <= 50) {
        p->s.velocityx = 3;
    }
    if (p->s.c[0] >= (xres - 50)) {
        p->s.velocityx = -3;
    }
    if (p->s.c[1] >= (game->altitude - 50)) {
        p->s.velocityy = -3;
    }
    if (p->s.c[1] <= (game->altitude - (yres - 50))) {
        p->s.velocityy = 3;
    }
	//limb restriction
	if(game->rarm1.s.rot > 151 || game->rarm1.s.rot < 19)
	{
		game->rarm1.s.rotInc = 0; 
	}
	if(game->rarm2.s.rot > 361 || game->rarm2.s.rot < 289)
	{
		game->rarm2.s.rotInc = 0;
	}
	if(game->larm1.s.rot > 311 || game->larm1.s.rot < 189)
	{
		game->larm1.s.rotInc = 0;
	}
	if(game->larm2.s.rot > 56 || game->larm2.s.rot < -1)
	{
		game->larm2.s.rotInc = 0;
	}
	if(game->rleg1.s.rot > 160 || game->rleg1.s.rot < 120)
	{
		game->rleg1.s.rotInc = 0;
	}
	if(game->rleg2.s.rot > 61 || game->rleg2.s.rot < 9)
	{
		game->rleg2.s.rotInc = 0;
	}
	if(game->lleg1.s.rot > 220 || game->lleg1.s.rot < 180)
	{
		game->lleg1.s.rotInc = 0;
	}
	if(game->lleg2.s.rot > 1 || game->lleg2.s.rot < -51)
	{
		game->lleg2.s.rotInc = 0;
	}

	//missile collision
	if(mis->s.center.x >= p->s.c[0] - p->s.width &&
	   mis->s.center.x <= p->s.c[0] + p->s.width &&
	   mis->s.center.y <= p->s.c[1] + p->s.height &&
	   mis->s.center.y >= p->s.c[1] - p->s.height)
	{
		mis->s.center.x = 0;
		mis->s.center.y = 0;
}
	//bird collision
	if(b->s.center.x >= p->s.c[0] - p->s.width &&
	   b->s.center.x <= p->s.c[0] + p->s.width &&
	   b->s.center.y < p->s.c[1] + p->s.height &&
	   b->s.center.y > p->s.c[1] - p->s.height)
	{
		game->health = game->health - 10;
		b->s.center.y += 100;		
    }
	if(b2->s.center.x >= p->s.c[0] - p->s.width &&
	   b2->s.center.x <= p->s.c[0] + p->s.width &&
	   b2->s.center.y < p->s.c[1] + p->s.height &&
	   b2->s.center.y > p->s.c[1] - p->s.height)
	{
		game->health = game->health - 10;
		b2->s.center.y += 100;		
    }

}


void render(Game *game)
{
	if(!start_flag) {
		glClear(GL_COLOR_BUFFER_BIT);
		//Pop default matrix onto current matrix
		glMatrixMode(GL_MODELVIEW);
		//Save default matrix again
		glPushMatrix();
		glTranslatef(0.f, gCameraY, 0.f);
		glColor3f(1.0, 1.0, 1.0);
		if (sky) {
			renderSky(game); 
		}
		renderMountain(game);
		renderCharacter(game);	
		BlueBirdRender(game);	
		BlueBirdRender2(game);
		MissileRender(game);
		displayAltitude(game);
		glPopMatrix();
	}

	if(start_flag) {
		glClear(GL_COLOR_BUFFER_BIT);
		glMatrixMode(GL_MODELVIEW);
		glPushMatrix();
		glColor3f(1.0, 1.0, 1.0);
		if (sky)
			renderSky(game);
		glPopMatrix();
	    renderStartMenu(game);	
	}
}
