/*
 * Filename:	alexA.cpp
 * Author:		Alex Avila
 * Purpose:		This cpp file defines functions declared in alexA.h
 */

#include "alexA.h"

int keys[65536];
void DefineRagdoll(Game *game)
{
    Character *c;

    //define body shape
    c = &game->body;
    c->s.width = 34;
    c->s.height = 73;
    c->s.c[0] = c->s.width/2;
    c->s.c[1] = c->s.height/2;
    //place body
    c->s.c[0] += 300.0;
    c->s.c[1] += 50;
    c->s.rotInc = 0.0f;
    c->s.rot = 30.0f;
    c->s.radius = 40.265;
    identity33(c->s.m);
    //head
    c = &game->head;
    c->s.width = 20;
    c->s.height = 30;
    c->s.c[0] = c->s.width/2;
    c->s.c[1] = 0;
    //place on body
    c->s.c[0] += -5;
    c->s.c[1] += -30;
    c->s.rotInc = 0.0f;
    c->s.rot = 330.0f;
    c->s.radius = 18.03;
    identity33(c->s.m);

    //define upper right arm
    c = &game->rarm1;
    c->s.width = 10;
    c->s.height = 40;
    c->s.c[0] = c->s.width/2;
    c->s.c[1] = 0;
    //place on body
    c->s.c[0] += 17;
    c->s.c[1] += 28;
    c->s.rotInc = -GRAVITY;
    c->s.rot = 75.0f;
    c->s.radius = 20.615;
    identity33(c->s.m);
    //define lower right arm
    c = &game->rarm2;
    c->s.width = 10;
    c->s.height = 40;
    c->s.c[0] = c->s.width/2;
    c->s.c[1] = 0;
    //place on upper arm
    c->s.c[0] += -5;
    c->s.c[1] += 30;
    c->s.rotInc = 0.0f;
    c->s.rot = 315.0f;
    c->s.radius = 20.615;
    identity33(c->s.m);

    //define upper left arm
    c = &game->larm1;
    c->s.width = 10;
    c->s.height = 40;
    c->s.c[0] = c->s.width/2;
    c->s.c[1] = 0;
    //place on body
    c->s.c[0] += -7;
    c->s.c[1] += 20;
    c->s.rotInc = GRAVITY;
    c->s.rot = 255.0f;
    c->s.radius = 20.615;
    identity33(c->s.m);
    //define lower left arm
    c = &game->larm2;
    c->s.width = 10;
    c->s.height = 40;
    c->s.c[0] = c->s.width/2;
    c->s.c[1] = 0;
    //place on upper arm
    c->s.c[0] += -5;
    c->s.c[1] += 30;
    c->s.rotInc = 0.0f;
    c->s.rot = 45.0f;
    c->s.radius = 20.615;
    identity33(c->s.m);

    //define right quad
    c = &game->rleg1;
    c->s.width = 10;
    c->s.height = 45;
    c->s.c[0] = c->s.width/2;
    c->s.c[1] = 0;
    //place quad on body
    c->s.c[0] += 18;
    c->s.c[1] += 5;
    c->s.rotInc = -GRAVITY;
    c->s.rot = 150.0f;
    c->s.radius = 23.045;
    identity33(c->s.m);
    //define right shin
    c = &game->rleg2;
    c->s.width = 15;
    c->s.height = 40;
    c->s.c[0] = c->s.width/2;
    c->s.c[1] = 0;
    //place shin on quad
    c->s.c[0] += -13;
    c->s.c[1] += 35;
    c->s.rotInc = 0.0f;
    c->s.rot = 15.0f;
    c->s.radius = 21.35;
    identity33(c->s.m);

    //define left quad
    c = &game->lleg1;
    c->s.width = 10;
    c->s.height = 45;
    c->s.c[0] = c->s.width/2;
    c->s.c[1] = 0;
    //place on body
    c->s.c[0] += 5;
    c->s.c[1] += 5;
    c->s.rotInc = GRAVITY;
    c->s.rot = 180.0f;
    c->s.radius = 23.045;
    identity33(c->s.m);
    //define left shin
    c = &game->lleg2;
    c->s.width = 15;
    c->s.height = 40;
    c->s.c[0] = c->s.width/2;
    c->s.c[1] = 0;
    //place shin on quad
    c->s.c[0] += -3;
    c->s.c[1] += 35;
    c->s.rotInc = 0.0f;
    c->s.rot = -15.0f;
    c->s.radius = 21.35;
    identity33(c->s.m);

    //parachute
    c = &game->par;
    c->s.width = 80;
    c->s.height = 150;
    c->s.c[0] = c->s.width;
    c->s.c[1] = 0;
    c->s.c[0] += 0;
    c->s.c[1] += 25;
    c->s.rot = 0;
    c->s.rotInc = 0;
    c->s.radius = 0;
    identity33(c->s.m);
}
void identity33(Matrix mat) {
    mat[0][0] = mat[1][1] = mat[2][2] = 1.0f;
    mat[0][1] = mat[0][2] = mat[1][0] = mat[1][2] = mat[2][0] = mat[2][1] = 0.0f;
}

void yy_transform(Flt rotate, Matrix a) {
    if(rotate != 0.0f)
    {
        Flt ct = cos(rotate), st = sin(rotate);
        Flt t00 = ct*a[0][0] - st*a[1][0];
        Flt t01 = ct*a[0][1] - st*a[1][1];
        Flt t02 = ct*a[0][2] - st*a[1][2];
        Flt t10 = st*a[0][0] + ct*a[1][0];
        Flt t11 = st*a[0][1] + ct*a[1][1];
        Flt t12 = st*a[0][2] + ct*a[1][2];
        a[0][0] = t00;
        a[0][1] = t01;
        a[0][2] = t02;
        a[1][0] = t10;
        a[1][1] = t11;
        a[1][2] = t12;
        return;
    }
}
void trans_vector(Matrix mat, const Vector in, Vector out) {
    Flt f0 = mat[0][0] * in[0] + mat[1][0] * in[1] + mat[2][0] * in[2];
    Flt f1 = mat[0][1] * in[0] + mat[1][1] * in[1] + mat[2][1] * in[2];
    Flt f2 = mat[0][2] * in[0] + mat[1][2] * in[1] + mat[2][2] * in[2];
    out[0] = f0;
    out[1] = f1;
    out[2] = f2;
}

void RagdollPhysics(Game *game)
{
    if(game->altitude <= 3000)
        game->parachute_flag = true;

    Character *p;
    Missile *mis = game->mhead;
    Bird *b = game->bhead;

    p = &game->body;

    if(p->s.rot == 360)
        p->s.rot = 0;

    if(game->parachute_flag == true)
    {
        if(p->s.velocityx > 0)
            game->par.s.rotInc += -0.1;
        if(p->s.velocityx < 0)
            game->par.s.rotInc += 0.1;
    }
    if (keys[XK_Right]) 
    {
        p->s.velocityx += 2;
        game->rarm1.s.rotInc += GRAVITY/8;
        game->larm1.s.rotInc += -GRAVITY/8;
        game->rleg1.s.rotInc += GRAVITY/8;
        game->lleg1.s.rotInc += GRAVITY/8;
        if(game->body.s.rot < 30.0)
            game->body.s.rotInc += 0.7f;
        else
            game->body.s.rotInc += 0.1f;

        game->rarm2.s.rotInc += -GRAVITY/16;
        game->larm2.s.rotInc += -GRAVITY/16;
        game->rleg2.s.rotInc += GRAVITY/16;
        game->lleg2.s.rotInc += -GRAVITY/16;
    }

    if (keys[XK_Left]) {
        p->s.velocityx += -2;
        game->rarm1.s.rotInc += -GRAVITY/8;
        game->larm1.s.rotInc += GRAVITY/8;
        game->rleg1.s.rotInc += -GRAVITY/8;
        game->lleg1.s.rotInc += -GRAVITY/8;

        if(game->body.s.rot > 30.0)
            game->body.s.rotInc += -0.7f;
        else
            game->body.s.rotInc += -0.1f;

        game->rarm2.s.rotInc += GRAVITY/16;
        game->larm2.s.rotInc += GRAVITY/16;
        game->rleg2.s.rotInc += -GRAVITY/16;
        game->lleg2.s.rotInc += GRAVITY/16;

    }
    if (keys[XK_Up]) {
        if (GRAVITY >= 3.0)
            GRAVITY -= 0.3;
        p->s.velocityy += 2;
        game->rarm1.s.rotInc += GRAVITY/8;
        game->larm1.s.rotInc += -GRAVITY/8;
        game->rleg1.s.rotInc += GRAVITY/8;
        game->lleg1.s.rotInc += -GRAVITY/8;

        game->rarm2.s.rotInc += GRAVITY/16;
        game->larm2.s.rotInc += -GRAVITY/16;
        game->rleg2.s.rotInc += -GRAVITY/16;
        game->lleg2.s.rotInc += GRAVITY/16;
    }

    if (keys[XK_Down]) {
        if (GRAVITY <= 15.0)
            GRAVITY += 0.3;
        p->s.velocityy -= 2;
        game->rarm1.s.rotInc += -GRAVITY/4;
        game->larm1.s.rotInc += GRAVITY/4;
        game->rleg1.s.rotInc += GRAVITY/4;
        game->lleg1.s.rotInc += GRAVITY/4;

        game->rarm2.s.rotInc += GRAVITY/8;
        game->larm2.s.rotInc += -GRAVITY/8;
        game->rleg2.s.rotInc += GRAVITY/8;
        game->lleg2.s.rotInc += -GRAVITY/8;
    }

    if(p->s.velocityy < 0)
    {
        game->rarm1.s.rotInc += -GRAVITY/32;
        game->larm1.s.rotInc += GRAVITY/32;
        game->rleg1.s.rotInc += GRAVITY/32;
        game->lleg1.s.rotInc += GRAVITY/32;

        game->rarm2.s.rotInc += GRAVITY/8;
        game->larm2.s.rotInc += -GRAVITY/8;
        game->rleg2.s.rotInc += GRAVITY/8;
        game->lleg2.s.rotInc += -GRAVITY/8;
    }
    if(p->s.velocityy > 0)
    {
        game->rarm1.s.rotInc += GRAVITY/32;
        game->larm1.s.rotInc += -GRAVITY/32;
        game->rleg1.s.rotInc += -GRAVITY/32;
        game->lleg1.s.rotInc += -GRAVITY/32;

        game->rarm2.s.rotInc += -GRAVITY/8;
        game->larm2.s.rotInc += GRAVITY/8;
        game->rleg2.s.rotInc += -GRAVITY/8;
        game->lleg2.s.rotInc += GRAVITY/8;
    }

    //parachute restriction
    if(game->par.s.rot < -26)
        game->par.s.rot = -25;
    if(game->par.s.rot > 26)
        game->par.s.rot = 25;
    //parachute body restriction
    if(game->parachute_flag)
    {
        if(game->body.s.rot > 76)
            game->body.s.rot = 75;
        if(game->body.s.rot < -1)
            game->body.s.rot = 0;
    }
    //right arm restriction
    if(game->rarm1.s.rot > 151)
        game->rarm1.s.rot = 150;
    if(game->rarm1.s.rot < 19)
        game->rarm1.s.rot = 20;

    if(game->rarm2.s.rot < 314)
        game->rarm2.s.rot = 315;
    if(game->rarm2.s.rot > 361)
        game->rarm2.s.rot = 360;
    //left arm restriction
    if(game->larm1.s.rot > 311)
        game->larm1.s.rot = 310;
    if(game->larm1.s.rot < 189)
        game->larm1.s.rot = 190;

    if(game->larm2.s.rot < -1)
        game->larm2.s.rot = 0;
    if(game->larm2.s.rot > 56)
        game->larm2.s.rot = 55;
    //right leg restriction
    if(game->rleg1.s.rot > 161)
        game->rleg1.s.rot = 160;
    if(game->rleg1.s.rot < 119)
        game->rleg1.s.rot = 120;
    if(game->rleg2.s.rot < 9)
        game->rleg2.s.rot = 10;
    if(game->rleg2.s.rot > 61)
        game->rleg2.s.rot = 60;
    //left leg restriction
    if(game->lleg1.s.rot < 180)
        game->lleg1.s.rot = 181;
    if(game->lleg1.s.rot > 220)
        game->lleg1.s.rot = 219;
    if(game->lleg2.s.rot > 1)
        game->lleg2.s.rot = 0;
    if(game->lleg2.s.rot < -51)
        game->lleg2.s.rot = -50;

    if(game->body.s.rotInc > 7)
        game->body.s.rotInc += -5.0f;
    if(game->body.s.rotInc < -7)
        game->body.s.rotInc += 5.0f;

    game->rarm1.s.rot += game->rarm1.s.rotInc;
    game->larm1.s.rot += game->larm1.s.rotInc;
    game->rleg1.s.rot += game->rleg1.s.rotInc;
    game->lleg1.s.rot += game->lleg1.s.rotInc;

    game->body.s.rot += game->body.s.rotInc;
    game->par.s.rot += game->par.s.rotInc;

    game->rarm2.s.rot += game->rarm2.s.rotInc;
    game->larm2.s.rot += game->larm2.s.rotInc;
    game->rleg2.s.rot += game->rleg2.s.rotInc;
    game->lleg2.s.rot += game->lleg2.s.rotInc;

    const Flt d2r = 1.0/360*3.14159265*2.0; //degrees to radians
    yy_transform(game->rleg1.s.rotInc*d2r, game->rleg1.s.m);
    yy_transform(game->lleg1.s.rotInc*d2r, game->lleg1.s.m);
    yy_transform(game->rarm1.s.rotInc*d2r, game->rarm1.s.m);
    yy_transform(game->larm1.s.rotInc*d2r, game->larm1.s.m);

    //parachute restriction
    if(game->par.s.rot > 25 || game->par.s.rot < -25)
        game->par.s.rotInc = 0;
    //parachute body restrition
    if(game->parachute_flag)
    {
        if(game->body.s.rot > 75)
            game->body.s.rotInc -= GRAVITY/4;
        if(game->body.s.rot < 0)
            game->body.s.rotInc += GRAVITY/4;
    }
    //limb restriction
    if(game->rarm1.s.rot > 151 || game->rarm1.s.rot < 19)
    {
        game->rarm1.s.rotInc = 0;
    }
    if(game->rarm2.s.rot > 361 || game->rarm2.s.rot < 289)
    {
        game->rarm2.s.rotInc = 0;
    }
    if(game->larm1.s.rot > 311 || game->larm1.s.rot < 189)
    {
        game->larm1.s.rotInc = 0;
    }
    if(game->larm2.s.rot > 56 || game->larm2.s.rot < -1)
    {
        game->larm2.s.rotInc = 0;
    }
    if(game->rleg1.s.rot > 160 || game->rleg1.s.rot < 120)
    {
        game->rleg1.s.rotInc = 0;
    }
    if(game->rleg2.s.rot > 61 || game->rleg2.s.rot < 9)
    {
        game->rleg2.s.rotInc = 0;
    }
    if(game->lleg1.s.rot > 220 || game->lleg1.s.rot < 180)
    {
        game->lleg1.s.rotInc = 0;
    }
    if(game->lleg2.s.rot > 1 || game->lleg2.s.rot < -51)
    {
        game->lleg2.s.rotInc = 0;
    }


    //missile collision
    while (mis) {
        float bodydist = sqrt(pow((p->s.c[0] - mis->s.center.x), 2) 
                + pow((p->s.c[1] - mis->s.center.y), 2));
        float headdist = sqrt(pow((game->head.s.c[0] - mis->s.center.x), 2) 
                + pow((game->head.s.c[1] - mis->s.center.y), 2));
        float rarm1dist = sqrt(pow((game->rarm1.s.c[0] - mis->s.center.x), 2) 
                + pow((game->rarm1.s.c[1] - mis->s.center.y), 2));
        float rarm2dist = sqrt(pow((game->rarm2.s.c[0] - mis->s.center.x), 2) 
                + pow((game->rarm2.s.c[1] - mis->s.center.y), 2));
        float larm1dist = sqrt(pow((game->larm1.s.c[0] - mis->s.center.x), 2) 
                + pow((game->larm1.s.c[1] - mis->s.center.y), 2));
        float larm2dist = sqrt(pow((game->larm2.s.c[0] - mis->s.center.x), 2) 
                + pow((game->larm2.s.c[1] - mis->s.center.y), 2));
        float rleg1dist = sqrt(pow((game->rleg1.s.c[0] - mis->s.center.x), 2) 
                + pow((game->rleg1.s.c[1] - mis->s.center.y), 2));
        float rleg2dist = sqrt(pow((game->rleg2.s.c[0] - mis->s.center.x), 2) 
                + pow((game->rleg2.s.c[1] - mis->s.center.y), 2));
        float lleg1dist = sqrt(pow((game->lleg1.s.c[0] - mis->s.center.x), 2) 
                + pow((game->lleg1.s.c[1] - mis->s.center.y), 2));
        float lleg2dist = sqrt(pow((game->lleg2.s.c[0] - mis->s.center.x), 2) 
                + pow((game->lleg2.s.c[1] - mis->s.center.y), 2));

        if(
                bodydist < p->s.radius + mis->s.radius ||
                headdist < game->head.s.radius + mis->s.radius ||
                rarm1dist < game->rarm1.s.radius + mis->s.radius ||
                rarm2dist < game->rarm2.s.radius + mis->s.radius ||
                larm1dist < game->larm1.s.radius + mis->s.radius ||
                larm2dist < game->larm2.s.radius + mis->s.radius ||
                rleg1dist < game->rleg1.s.radius + mis->s.radius ||
                rleg2dist < game->rleg2.s.radius + mis->s.radius ||
                lleg1dist < game->lleg1.s.radius + mis->s.radius ||
                lleg2dist < game->lleg2.s.radius + mis->s.radius
          )
        {
            playSound("missileLoud");
            deleteMissile(game, mis);
            p->s.velocityy += mis->velocity.y;
            p->s.rotInc = 2*GRAVITY;
            game->hits = game->hits + 1;
            game->health = game->health - mis->velocity.y/2;
        }
        mis = mis->next;
    }

    //bird collision
    while (b) {
	float bbodydist = sqrt(pow((p->s.c[0] - b->s.center.x), 2)
                + pow((p->s.c[1] - b->s.center.y), 2));
        float bheaddist = sqrt(pow((game->head.s.c[0] - b->s.center.x), 2)
                + pow((game->head.s.c[1] - b->s.center.y), 2));
        float brarm1dist = sqrt(pow((game->rarm1.s.c[0] - b->s.center.x), 2)
                + pow((game->rarm1.s.c[1] - b->s.center.y), 2));
        float brarm2dist = sqrt(pow((game->rarm2.s.c[0] - b->s.center.x), 2)
                + pow((game->rarm2.s.c[1] - b->s.center.y), 2));
        float blarm1dist = sqrt(pow((game->larm1.s.c[0] - b->s.center.x), 2)
                + pow((game->larm1.s.c[1] - b->s.center.y), 2));
        float blarm2dist = sqrt(pow((game->larm2.s.c[0] - b->s.center.x), 2)
                + pow((game->larm2.s.c[1] - b->s.center.y), 2));
        float brleg1dist = sqrt(pow((game->rleg1.s.c[0] - b->s.center.x), 2)
                + pow((game->rleg1.s.c[1] - b->s.center.y), 2));
        float brleg2dist = sqrt(pow((game->rleg2.s.c[0] - b->s.center.x), 2)
                + pow((game->rleg2.s.c[1] - b->s.center.y), 2));
        float blleg1dist = sqrt(pow((game->lleg1.s.c[0] - b->s.center.x), 2)
                + pow((game->lleg1.s.c[1] - b->s.center.y), 2));
        float blleg2dist = sqrt(pow((game->lleg2.s.c[0] - b->s.center.x), 2)
                + pow((game->lleg2.s.c[1] - b->s.center.y), 2));

        if(
                bbodydist < p->s.radius + b->s.radius ||
                bheaddist < game->head.s.radius + b->s.radius ||
                brarm1dist < game->rarm1.s.radius + b->s.radius ||
                brarm2dist < game->rarm2.s.radius + b->s.radius ||
                blarm1dist < game->larm1.s.radius + b->s.radius ||
                blarm2dist < game->larm2.s.radius + b->s.radius ||
                brleg1dist < game->rleg1.s.radius + b->s.radius ||
                brleg2dist < game->rleg2.s.radius + b->s.radius ||
                blleg1dist < game->lleg1.s.radius + b->s.radius ||
                blleg2dist < game->lleg2.s.radius + b->s.radius
          )
                {
                     p->s.rotInc += GRAVITY/4;
                     p->s.velocityx += b->velocity.x;
                     deleteBlueBird(game, b);
                     game->hits = game->hits + 1;
                     if (b->c.blue) {
			 game->health = game->health - abs(b->velocity.x)/10;
	             } else if (b->c.red) {
			 game->health = game->health - abs(b->velocity.x)/10;
	             } else if (b->c.green) {
			 game->health = game->health + abs(b->velocity.x)/10;
		     } else if (b->c.orange) {
			game->health = game->health - abs(b->velocity.x)/10;
	             } else if (b->c.purple) {
			if (rand()%2 < 1) {
	 		    game->health = game->health - abs(b->velocity.x)/10;
			} else {
			    game->health = game->health + abs(b->velocity.x)/10;
			}
                     }			
                 }
        b = b->next;
    }
}
