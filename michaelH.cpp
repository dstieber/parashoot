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
