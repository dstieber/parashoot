#ifndef _JONP_H_
#define _JONP_H_

#define USE_SOUND
#ifdef USE_SOUND
#include <FMOD/fmod.h>
#include <FMOD/fmod_errors.h>
#include <FMOD/wincompat.h>
#include "fmod.h"
#endif

void play();
void create_sounds();
#endif
