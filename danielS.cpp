/*
 * Filename:	danielS.cpp
 * Author:		Daniel Stieber
 * Purpose:		This cpp file defines functions declared in danielS.h
 *
 */

#include "danielS.h"

Ppmimage *skyImage = NULL;
Ppmimage *characterImage = NULL;
GLuint skyTexture;
GLuint silhouetteTexture;

void initSky(void) 
{
    skyImage = ppm6GetImage("./images/Sky.ppm");
    glGenTextures(1, &skyTexture);
    glBindTexture(GL_TEXTURE_2D, skyTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    glTexImage2D(GL_TEXTURE_2D, 0, 3, skyImage->width, skyImage->height,
            0, GL_RGB, GL_UNSIGNED_BYTE, skyImage->data);
}

void renderSky(Game *game) 
{
    glBindTexture(GL_TEXTURE_2D, skyTexture);
    glBegin(GL_QUADS);
    int ybottom = game->altitude - yres;
    glTexCoord2f(0.0f, 1.0f); glVertex2i(0, ybottom);
    glTexCoord2f(0.0f, 0.0f); glVertex2i(0, game->altitude);
    glTexCoord2f(1.0f, 0.0f); glVertex2i(xres, game->altitude);
    glTexCoord2f(1.0f, 1.0f); glVertex2i(xres, ybottom);
    glEnd();
}

void initCharacter(void) 
{
    characterImage = ppm6GetImage("./images/character1.ppm");
    glGenTextures(1, &silhouetteTexture);
    glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_NEAREST);
    unsigned char *silhouetteData = buildAlphaData(characterImage);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, characterImage->width, 
            characterImage->height, 0, GL_RGBA, GL_UNSIGNED_BYTE, silhouetteData);
    delete [] silhouetteData;
}

void renderCharacter(Game *game)
{
    float w, h;
    Vec *c = &game->character.s.center;
    w = 49;
    h = 79;
    glBindTexture(GL_TEXTURE_2D, silhouetteTexture);
    glEnable(GL_ALPHA_TEST);
    glAlphaFunc(GL_GREATER, 0.0f);
    glColor4ub(255,255,255,255);
    glBegin(GL_QUADS);
    if (game->character.velocity.x < 0) {
        glTexCoord2f(0.0f, 1.0f); glVertex2i(c->x-w, c->y-h);
        glTexCoord2f(0.0f, 0.0f); glVertex2i(c->x-w, c->y+h);
        glTexCoord2f(0.5f, 0.0f); glVertex2i(c->x+w, c->y+h);
        glTexCoord2f(0.5f, 1.0f); glVertex2i(c->x+w, c->y-h);
        glEnd();
    }
    if (game->character.velocity.x >= 0) {
        glTexCoord2f(0.5f, 1.0f); glVertex2i(c->x-w, c->y-h);
        glTexCoord2f(0.5f, 0.0f); glVertex2i(c->x-w, c->y+h);
        glTexCoord2f(1.0f, 0.0f); glVertex2i(c->x+w, c->y+h);
        glTexCoord2f(1.0f, 1.0f); glVertex2i(c->x+w, c->y-h);
        glEnd();
    }
}

void displayAltitude(Game *game) 
{
    int i = STARTING_ALTITUDE;
    while (i > 0) {
        if ((game->altitude < (i + yres/2)) && (game->altitude > (i - yres/2))) {
            Rect r;
            char cstr[10];
            r.left = xres - 50;
            r.bot = i - yres/2;
            r.center = xres - 50;
            r.width = 500;
            r.height = 100;
            sprintf (cstr, "%d", i);
            strcat (cstr, "ft");
            ggprint16(&r, 16, 0xdd4814, "%s", cstr);
        }
        i = i - 100;
    }
}

void renderStartMenu(Game *game)
{       
    Rect start;
    Rect click;

    start.bot = game->altitude - yres/4;
    start.width = 500;
    start.height = 100;
    start.center = xres/2 + yres/4;
    start.left = xres/2;

    click.bot = game->altitude - yres/2;
    click.width = 500;
    click.height = 100;
    click.center = xres/2;
    click.left = xres/2;

    ggprint16(&start, 1000, 0x00fff000, "PARASHOOT!");
    ggprint16(&click, 1000, 0x00fff000, "Click to start");
}

void randomGenerator(Game *game) 
{
    srand (time(NULL));

    if (rand()%10 < 9) 
    {
        MakeBlueBird(game);
        BlueBirdRender(game);
    }

}

void deleteBlueBird(Game *game, Bird *node)
{
    if (game->bhead != NULL) {
        if (node->prev == NULL) {
            if (node->next == NULL) {
                game->bhead = NULL;
            } else {
                node->next->prev = NULL;
                game->bhead = node->next;
            }
        } else {
            if (node->next == NULL) {
                node->prev->next = NULL;
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
        }
        delete node;
        node = NULL;
    }
}

void deleteRedBird(Game *game, Bird2 *node)
{
    if (game->bhead2 != NULL) {
        if (node->prev == NULL) {
            if (node->next == NULL) {
                game->bhead2 = NULL;
            } else {
                node->next->prev = NULL;
                game->bhead2 = node->next;
            }
        } else {
            if (node->next == NULL) {
                node->prev->next = NULL;
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
        }
        delete node;
        node = NULL;
    }
}

void deleteMissile(Game *game, Missile *node)
{
    if (game->mhead != NULL) {
        if (node->prev == NULL) {
            if (node->next == NULL) {
                game->mhead = NULL;
            } else {
                node->next->prev = NULL;
                game->mhead = node->next;
            }
        } else {
            if (node->next == NULL) {
                node->prev->next = NULL;
            } else {
                node->prev->next = node->next;
                node->next->prev = node->prev;
            }
        }
        delete node;
        node = NULL;
    }
}
