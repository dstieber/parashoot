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
	//unsigned char color[3];
};

struct Character {
	Shape s;
	Vec velocity;
};

struct Object {
	Shape s;
	Vec velocity;
};

struct Bird {
	Shape s;
	Vec velocity;
	struct Bird *prev;
	struct Bird *next;
	Bird() {
		prev = NULL;
		next = NULL;
	}
};

struct Bird2 {
    Shape s;
    Vec velocity;
    struct Bird2 *prev;
    struct Bird2 *next;
    Bird2() {
        prev = NULL;
        next = NULL;
    }
};

struct Missile {
	Shape s;
	Vec velocity;
	struct Missile *prev;
	struct Missile *next;
	Missile() {
		prev = NULL;
		next = NULL;
	}
};

struct Cloud {
	Shape s;
	Vec velocity;
	struct Cloud *prev;
	struct Cloud *next;
	Cloud() {
		prev = NULL;
		next = NULL;
	}
};

struct Game {
	Character head, body, rarm1, rarm2, larm1, larm2, rleg1, rleg2,
			  lleg1, lleg2;
	//Shape box;
	Character character;
	Character BlueBird;
	Character BlueBird2;
	Missile missile;
	Object Cloud2;
	Object Cloud1;
	Object Mountain;
	Object Plane;
	Object Logo;
	Bird *bhead; //pointer to head of bird linked list
	Missile *mhead; //pointer to head of missile linked list
	Cloud *chead; //pointer to head of cloud linked list
	int n;
	int health;
	int nbirds;
	int nmissiles;
	int nclouds;
	float altitude;
	Game() {
		health = 100;
		altitude = (float)STARTING_ALTITUDE;
		bhead = NULL;
		mhead = NULL;
		nbirds = 0;
		nmissiles = 0;
		nclouds = 0;
		n = 0;
	}
};

#endif
