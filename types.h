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

typedef float Flt;
typedef Flt Vector[3];
typedef Flt Matrix[3][3];

struct Vec {
    float x, y, z;
};

struct Shape {
    float width, height;
    float radius;
    Vec center;
    Vector c;
    float velocityx, velocityy;
    Flt rot, rotInc;
    Matrix m;
    unsigned char color[3];
};

struct Character {
    Shape s;
    Vec velocity;
};

struct Game {
    Character box, body, rarm1, rarm2, larm1, larm2, rleg1, rleg2,
		lleg1, lleg2;
    Character character;
    Character BlueBird;
    Character BlueBird2;
    Character Missile;
    int n;
    int health;
    float altitude;
    Game() {
	health = 100;
	altitude = (float)STARTING_ALTITUDE;
	n = 0;
    }
};

#endif
