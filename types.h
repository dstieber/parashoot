#ifndef TYPES_H
#define TYPES_H
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
extern "C" {
#include "fonts.h"
}

#define GRAVITY 3.0
#define STARTING_ALTITUDE 12000
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
    Character BlueBird;
    Character BlueBird2;
    int n;
    float altitude;
    Game() {
	altitude = (float)STARTING_ALTITUDE;
	n = 0;
    }
};

#endif
