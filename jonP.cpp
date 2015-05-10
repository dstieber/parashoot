#include "jonP.h"

void create_sounds() {
#ifdef USE_SOUND
    if(fmod_init()) {
	printf("ERROR");
	return;
    }
    if(fmod_createsound((char *)"./sounds/Highly_Suspicious.mp3", 0)) {
	printf("ERROR");
	return;
    }
    fmod_setmode(0, FMOD_LOOP_NORMAL);
#endif
}

void play() {
    fmod_playsound(0);
}
