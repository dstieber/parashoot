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

extern double WingDiff(struct timespec *start, struct timespec *end);
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
	double Wingspan;
	struct timespec Wingdown;
	struct timespec Wingcurrent;
	Bird() {
		clock_gettime(CLOCK_REALTIME, &Wingdown);
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
	bool parachute_flag;
	bool end_of_game;
	Bird *bhead; //pointer to head of bird linked list
	Missile *mhead; //pointer to head of missile linked list
	int n;
	int health;
	int nbirds;
	int nmissiles;
	float altitude;
	Game() {
		end_of_game = false;
		parachute_flag = false;
		health = 100;
		altitude = (float)STARTING_ALTITUDE;
		bhead = NULL;
		mhead = NULL;
		nbirds = 0;
		nmissiles = 0;
		n = 0;
	}
};

#endif
