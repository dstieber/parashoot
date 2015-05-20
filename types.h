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
#define MAX 50

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

struct Object {
    Shape s;
    Vec velocity;
};

struct Game {
    Shape box;
    Character character;

    Character BlueBird;
    Character *BlueBird2;
    Object Missile;
    Object Cloud2;
    Object Cloud1;
    Object Mountain;
    Object Plane;

    int n;
    ~Game() { delete [] BlueBird2; }
    float altitude;
    Game() {
	altitude = (float)STARTING_ALTITUDE;
	BlueBird2 = new Character[MAX];
	n = 0;
    }
};

#endif
