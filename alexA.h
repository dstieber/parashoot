// ALexzander Avila
#ifndef _ALEXA_H_
#define _ALEXA_H_

#include <iostream>
#include <cstdlib>
#include <cstring>
#include <cmath>
#include <X11/Xlib.h>
#include <X11/keysym.h>
#include <GL/glx.h>
#include "types.h"
#define STARTING_ALTITUDE 12000

typedef float Flt;
typedef Flt Vector[3];
typedef Flt Matrix[3][3];

void DefineRagdoll(Game *);
void RagdollPhysics(Game *);
void init_keys();
void identity33(Matrix mat);
void yy_transform(Flt rotate, Matrix a);
void trans_vector(Matrix mat, const Vector in, Vector out);
#endif
