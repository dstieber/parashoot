#ifndef TYPES_H
#define TYPES_H
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cstring>
#include <string>
#include <cmath>
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


//#define GRAVITY 30.0
#define STARTING_ALTITUDE 24000
extern double WingDiff(struct timespec *start, struct timespec *end);
typedef float Flt;
typedef Flt Vector[3];
typedef Flt Matrix[3][3];

struct Color {
    bool blue, red, green, orange, purple;
};

struct ColorM {
    bool green, yellow, blue, red;
};

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
	Color c;
	struct Bird *prev;
	struct Bird *next;
	double Wingspan;
	struct timespec Wingdown;
	struct timespec Wingcurrent;
	Bird() {
		clock_gettime(CLOCK_REALTIME, &Wingdown);
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
	ColorM c;
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

struct Planes {
	Shape s;
	Vec velocity;
	struct Planes *prev;
	struct Planes *next;
	Planes() {
		prev = NULL;
		next = NULL;
	}
};

struct Game {
	Character head, body, rarm1, rarm2, larm1, larm2, rleg1, rleg2,
			  lleg1, lleg2, par;
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
	bool parachute_flag;
	bool end_of_game;
	Bird *bhead; //pointer to head of bird linked list
	Missile *mhead; //pointer to head of missile linked list
	Cloud *chead; //pointer to head of cloud linked list
	Planes *phead; //pointer to head of plane linked list
	int n;
	int health;
    int hits;
	int nbirds;
	int nmissiles;
	int nclouds;
	int nplanes;
	float altitude;
	Game() {
		end_of_game = false;
		parachute_flag = false;
		health = 100;
		hits = 0;
		altitude = (float)STARTING_ALTITUDE;
		bhead = NULL;
		mhead = NULL;
		nbirds = 0;
		nmissiles = 0;
		nclouds = 0;
		nplanes = 0;
		n = 0;
	}
};

#endif
