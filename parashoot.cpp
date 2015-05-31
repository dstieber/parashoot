#include "parashoot.h"

int main(void)
{
    int done=0;
    srand(time(NULL));
    initXWindows();
    init_opengl(&game);
    DefineRagdoll(&game);
    init_keys();
    create_sounds();
    play();
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
    InitCloud();
    InitCloud2();
    InitMountain();
    InitBlueBird();
    //InitBlueBird2();
    InitMissile();
    InitPlane();
    //create opengl texture elements

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
    MakeMountain(game);
    MakeCloud(game);
    MakeCloud2(game);
    MakePlane(game);
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
    if (game->altitude < 0)
	end_flag = true;

    if (start_flag)
	return;

    Character *p;
    p = &game->body;
    p->s.c[0] += p->s.velocityx;
    p->s.c[1] += p->s.velocityy;
    p->s.c[1] -= GRAVITY;
    game->altitude -= GRAVITY;
    RagdollPhysics(game);
    gCameraY += (float)GRAVITY;
    //check for collision with objects here...
    //border collision detection
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

    MountainMovement(game);

    if (!end_flag) {
	
		if (rand()%10 < 1) {
	    	MakeBlueBird(game);
		}
	
		if (rand()%50 < 1) {
	    	if (game->altitude > 1500) {
				MakeMissile(game);
			}
		}

		if (rand()%150 < 1) {
			MakeRandomCloud(game);
		}
    }

    BlueBirdMovement(game);
    MissileMovement(game);
    CloudMovement(game);
    Cloud2Movement(game);
    randomCloudMovement(game);	
	PlaneMovement(game);
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
	renderCloud2(game);
	renderMountain(game);
	renderCloud(game);
	renderPlane(game);
	renderCharacter(game);
	BlueBirdRender(game);	
	MissileRender(game);
	renderRandomCloud(game);
	displayAltitude(game);
	glPopMatrix();
    }

	if (end_flag) {
		renderGameOver(game);
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
