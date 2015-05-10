#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <cmath>
#include <string>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include <GL/gl.h>
#include <GL/glu.h>
#include <stdio.h>
#include <stdlib.h>
#include <X11/Xutil.h>
#include "log.h"
#include "ppm.h"
#include "danielS.h"
#include "jonP.h"
#include "michaelH.h"
#include "alexB.h"
extern "C" {
#include "fonts.h"
}
#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 800
#define STARTING_ALTITUDE 12000
#define MAX_PARTICLES 1
#define GRAVITY 3.0
#define USE_SOUND
//X Windows variables
Display *dpy;
Window win;
GLXContext glc;

int xres = WINDOW_WIDTH;
int yres = WINDOW_HEIGHT;
bool size_flag = false;
bool start_flag = true;

//Camera position
GLfloat gCameraY = 0.0f;

Ppmimage *skyImage = NULL;
Ppmimage *characterImage = NULL;
Ppmimage *mountainImage = NULL;
GLuint skyTexture;
GLuint mountainTexture;
GLuint characterTexture;
GLuint silhouetteTexture;
GLuint msilhouetteTexture;
int sky = 1;
int character = 1;
int keys[65536];
struct Vec {
    float x, y, z;
};

struct Shape {
    float width, height;
    float radius;
    Vec center;
};

struct Character {
    Shape s;
    Vec velocity;
};

struct Game {
    Shape box;
    Character character;
    int n;
    float altitude;
    Game() {
	altitude = (float)STARTING_ALTITUDE;
	n = 0;
    }
};

//Function prototypes
void initXWindows(void);
void init_opengl(Game *game);
void cleanupXWindows(void);
void check_mouse(XEvent *e, Game *game);
int check_keys(XEvent *e);
void movement(Game *game);
void render(Game *game);
void check_resize(Game *game, XEvent *e);
//void create_sounds();
//void play();
void init_keys();
//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 30.0;
const double oobillion = 1.0 / 1e9;
struct timespec timeStart, timeCurrent;
struct timespec timePause;
double physicsCountdown=0.0;
double timeSpan=0.0;
double timeDiff(struct timespec *start, struct timespec *end) {
    return (double)(end->tv_sec - start->tv_sec ) +
	(double)(end->tv_nsec - start->tv_nsec) * oobillion;
}
void timeCopy(struct timespec *dest, struct timespec *source) {
    memcpy(dest, source, sizeof(struct timespec));
}
//-----------------------------------------------------------------------------

Game game;
