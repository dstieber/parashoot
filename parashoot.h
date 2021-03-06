#include "danielS.h"
#include "jonP.h"
#include "michaelH.h"
#include "alexA.h"
#include "types.h"
#define WINDOW_WIDTH  1396
#define WINDOW_HEIGHT 1018
#define USE_SOUND
//X Windows variables
Display *dpy;
Window win;
GLXContext glc;
float GRAVITY = 3.0;
float MAX_GRAVITY = 16.0;
Game game;
XEvent e;
int xres = WINDOW_WIDTH;
int yres = WINDOW_HEIGHT;
bool size_flag = false;
bool menu_flag = true;
bool start_flag = false;
bool end_flag = false;
//Camera position
GLfloat gCameraY = 0.0f;

//Ppmimage *mountainImage = NULL;
//GLuint mountainTexture;
GLuint characterTexture;
//GLuint msilhouetteTexture;
int sky = 1;
int character = 1;

//Function prototypes
void initXWindows(void);
void init_opengl(Game *game);
void cleanupXWindows(void);
void check_mouse(XEvent *e, Game *game);
int check_keys(XEvent *e);
void movement(Game *game);
void render(Game *game);
void check_resize(Game *game, XEvent *e);
void init_keys();
//-----------------------------------------------------------------------------
//Setup timers
const double physicsRate = 1.0 / 30.0;
const double oobillion = 1.0 / 1e9;
const double oomillion = 1.0 / 1e8;
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
double WingDiff(struct timespec *start, struct timespec *end) {
    return (double)(end->tv_sec - start->tv_sec ) +
	(double)(end->tv_nsec - start->tv_nsec) * oomillion;
}
//-----------------------------------------------------------------------------
