// Michael Harp
#include "michaelH.h"

void renderMountain(Game *game) {
    glBindTexture(GL_TEXTURE_2D, msilhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255, 255, 255, 255);
    glBegin(GL_QUADS);
    int ybottom = game->altitude - yres;	
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, ybottom);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, game->altitude);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, game->altitude);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, ybottom);
    glEnd();
}

void init_keys() {
    memset(keys, 0, 65536);
}

int check_keys(XEvent *e)
{
    //keyboard input?
    static int shift=0;
    int key = XLookupKeysym(&e->xkey, 0);
    //Log("key: %i\n", key);
    if (e->type == KeyRelease) {
        keys[key]=0;
        if (key == XK_Shift_L || key == XK_Shift_R)
            shift=0;
        return 0;
    }
    if (e->type == KeyPress) {
        keys[key]=1;
        if (key == XK_Shift_L || key == XK_Shift_R) {
            shift=1;
            return 0;
        }
    } else {
        return 0;
    }
    if (shift){}
    switch(key) {
        case XK_Escape:
            return 1;
        case XK_f:
            break;
        case XK_s:
            break;
        case XK_Down:
            break;
        case XK_equal:
            break;
        case XK_minus:
            break;
    }
    return 0;
}

