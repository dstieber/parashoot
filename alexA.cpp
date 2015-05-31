// Alexzander Avila
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
    identity33(c->s.m);
}
void identity33(Matrix mat)
{
    mat[0][0] = mat[1][1] = mat[2][2] = 1.0f;
    mat[0][1] = mat[0][2] = mat[1][0] = mat[1][2] = mat[2][0] = mat[2][1] = 0.0f;
}
void yy_transform(Flt rotate, Matrix a)
{
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
void trans_vector(Matrix mat, const Vector in, Vector out)
{
    Flt f0 = mat[0][0] * in[0] + mat[1][0] * in[1] + mat[2][0] * in[2];
    Flt f1 = mat[0][1] * in[0] + mat[1][1] * in[1] + mat[2][1] * in[2];
    Flt f2 = mat[0][2] * in[0] + mat[1][2] * in[1] + mat[2][2] * in[2];
    out[0] = f0;
    out[1] = f1;
    out[2] = f2;
}

void RagdollPhysics(Game *game)
{
    if (!end_flag) {
	Character *p;
	Missile *mis = game->mhead;
	Bird *b = game->bhead;
	//Character *b2 = &game->BlueBird2;

	p = &game->body;

	if(p->s.rot == 360)
	{
	    p->s.rot = 0;
	}

	if (keys[XK_Right]) {
	    p->s.velocityx += 2;
	    game->rarm1.s.rotInc += GRAVITY/8;
	    game->larm1.s.rotInc += -GRAVITY/8;
	    game->rleg1.s.rotInc += GRAVITY/8;
	    game->lleg1.s.rotInc += GRAVITY/8;

	    if(game->body.s.rot < 30.0)
	    {
		game->body.s.rotInc += 0.7f;
	    }
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
	    {
		game->body.s.rotInc += -0.7f;
	    }
	    else
		game->body.s.rotInc += -0.1f;

	    game->rarm2.s.rotInc += GRAVITY/16;
	    game->larm2.s.rotInc += GRAVITY/16;
	    game->rleg2.s.rotInc += -GRAVITY/16;
	    game->lleg2.s.rotInc += GRAVITY/16;

	}
	if (keys[XK_Up]) {
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

	//right arm restriction
	if(game->rarm1.s.rot > 151)
	{
	    game->rarm1.s.rot = 150;
	}
	if(game->rarm1.s.rot < 19)
	{
	    game->rarm1.s.rot = 20;
	}

	if(game->rarm2.s.rot < 289)
	{
	    game->rarm2.s.rot = 290;
	}
	if(game->rarm2.s.rot > 361)
	{
	    game->rarm2.s.rot = 360;
	}
	//left arm restriction
	if(game->larm1.s.rot > 311)
	{
	    game->larm1.s.rot = 310;
	}
	if(game->larm1.s.rot < 189)
	{
	    game->larm1.s.rot = 190;
	}

	if(game->larm2.s.rot < -1)
	{
	    game->larm2.s.rot = 0;
	}
	if(game->larm2.s.rot > 56)
	{
	    game->larm2.s.rot = 55;
	}
	//right leg restriction
	if(game->rleg1.s.rot > 161)
	{
	    game->rleg1.s.rot = 160;
	}
	if(game->rleg1.s.rot < 119)
	{
	    game->rleg1.s.rot = 120;
	}
	if(game->rleg2.s.rot < 9)
	{
	    game->rleg2.s.rot = 10;
	}
	if(game->rleg2.s.rot > 61)
	{
	    game->rleg2.s.rot = 60;
	}
	//left leg restriction
	if(game->lleg1.s.rot < 180)
	{
	    game->lleg1.s.rot = 181;
	}
	if(game->lleg1.s.rot > 220)
	{
	    game->lleg1.s.rot = 219;
	}
	if(game->lleg2.s.rot > 1)
	{
	    game->lleg2.s.rot = 0;
	}
	if(game->lleg2.s.rot < -51)
	{
	    game->lleg2.s.rot = -50;
	}

	if(game->body.s.rotInc > 7)
	{
	    game->body.s.rotInc += -5.0f;
	}
	if(game->body.s.rotInc < -7)
	{
	    game->body.s.rotInc += 5.0f;
	}

	game->rarm1.s.rot += game->rarm1.s.rotInc;
	game->larm1.s.rot += game->larm1.s.rotInc;
	game->rleg1.s.rot += game->rleg1.s.rotInc;
	game->lleg1.s.rot += game->lleg1.s.rotInc;

	game->body.s.rot += game->body.s.rotInc;

	game->rarm2.s.rot += game->rarm2.s.rotInc;
	game->larm2.s.rot += game->larm2.s.rotInc;
	game->rleg2.s.rot += game->rleg2.s.rotInc;
	game->lleg2.s.rot += game->lleg2.s.rotInc;

	const Flt d2r = 1.0/360*3.14159265*2.0; //degrees to radians
	yy_transform(game->rleg1.s.rotInc*d2r, game->rleg1.s.m);
	yy_transform(game->lleg1.s.rotInc*d2r, game->lleg1.s.m);
	yy_transform(game->rarm1.s.rotInc*d2r, game->rarm1.s.m);
	yy_transform(game->larm1.s.rotInc*d2r, game->larm1.s.m);

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
	    if(
		    (mis->s.center.x >= p->s.c[0] - p->s.width &&
		     mis->s.center.x <= p->s.c[0] + p->s.width &&
		     mis->s.center.y < p->s.c[1] + p->s.height &&
		     mis->s.center.y > p->s.c[1] - p->s.height)
		    ||
		    (mis->s.center.x >= game->head.s.c[0] - game->head.s.width &&
		     mis->s.center.x <= game->head.s.c[0] + game->head.s.width &&
		     mis->s.center.y < game->head.s.c[1] + game->head.s.height &&
		     mis->s.center.y > game->head.s.c[1] - game->head.s.height)
		    ||
		    (mis->s.center.x >= game->rarm1.s.c[0] - game->rarm1.s.width &&
		     mis->s.center.x <= game->rarm1.s.c[0] + game->rarm1.s.width &&
		     mis->s.center.y < game->rarm1.s.c[1] + game->rarm1.s.height &&
		     mis->s.center.y > game->rarm1.s.c[1] - game->rarm1.s.height)
		    ||
		    (mis->s.center.x >= game->rarm2.s.c[0] - game->rarm2.s.width &&
		     mis->s.center.x <= game->rarm2.s.c[0] + game->rarm2.s.width &&
		     mis->s.center.y < game->rarm2.s.c[1] + game->rarm2.s.height &&
		     mis->s.center.y > game->rarm2.s.c[1] - game->rarm2.s.height)
		    ||
		    (mis->s.center.x >= game->rleg1.s.c[0] - game->rleg1.s.width &&
		     mis->s.center.x <= game->rleg1.s.c[0] + game->rleg1.s.width &&
		     mis->s.center.y < game->rleg1.s.c[1] + game->rleg1.s.height &&
		     mis->s.center.y > game->rleg1.s.c[1] - game->rleg1.s.height)
		    ||
		    (mis->s.center.x >= game->rleg2.s.c[0] - game->rleg2.s.width &&
		     mis->s.center.x <= game->rleg2.s.c[0] + game->rleg2.s.width &&
		     mis->s.center.y < game->rleg2.s.c[1] + game->rleg2.s.height &&
		     mis->s.center.y > game->rleg2.s.c[1] - game->rleg2.s.height)
		    ||
		    (mis->s.center.x >= game->lleg1.s.c[0] - game->lleg1.s.width &&
		     mis->s.center.x <= game->lleg1.s.c[0] + game->lleg1.s.width &&
		     mis->s.center.y < game->lleg1.s.c[1] + game->lleg1.s.height &&
		     mis->s.center.y > game->lleg1.s.c[1] - game->lleg1.s.height)
		    ||
		    (mis->s.center.x >= game->lleg2.s.c[0] - game->lleg2.s.width &&
		     mis->s.center.x <= game->lleg2.s.c[0] + game->lleg2.s.width &&
		     mis->s.center.y < game->lleg2.s.c[1] + game->lleg2.s.height &&
		     mis->s.center.y > game->lleg2.s.c[1] - game->lleg2.s.height)
		    ||
		    (mis->s.center.x >= game->larm1.s.c[0] - game->larm1.s.width &&
		     mis->s.center.x <= game->larm1.s.c[0] + game->larm1.s.width &&
		     mis->s.center.y < game->larm1.s.c[1] + game->larm1.s.height &&
		     mis->s.center.y > game->larm1.s.c[1] - game->larm1.s.height)
		    ||
		    (mis->s.center.x >= game->larm2.s.c[0] - game->larm2.s.width &&
		     mis->s.center.x <= game->larm2.s.c[0] + game->larm2.s.width &&
		     mis->s.center.y < game->larm2.s.c[1] + game->larm2.s.height &&
		     mis->s.center.y > game->larm2.s.c[1] - game->larm2.s.height))
		     {
			 deleteMissile(game, mis);
			 p->s.velocityy += 20;
			 p->s.rotInc = 2*GRAVITY;
		     }
	    mis = mis->next;
	}


	//bird collision
	while (b) {

	    if((b->s.center.x >= p->s.c[0] - p->s.width &&
			b->s.center.x <= p->s.c[0] + p->s.width &&
			b->s.center.y < p->s.c[1] + p->s.height &&
			b->s.center.y > p->s.c[1] - p->s.height)
		    ||
		    (b->s.center.x >= game->head.s.c[0] - game->head.s.width &&
		     b->s.center.x <= game->head.s.c[0] + game->head.s.width &&
		     b->s.center.y < game->head.s.c[1] + game->head.s.height &&
		     b->s.center.y > game->head.s.c[1] - game->head.s.height)
		    ||
		    (b->s.center.x >= game->rarm1.s.c[0] - game->rarm1.s.width &&
		     b->s.center.x <= game->rarm1.s.c[0] + game->rarm1.s.width &&
		     b->s.center.y < game->rarm1.s.c[1] + game->rarm1.s.height &&
		     b->s.center.y > game->rarm1.s.c[1] - game->rarm1.s.height)
		    ||
		    (b->s.center.x >= game->larm1.s.c[0] - game->larm1.s.width &&
		     b->s.center.x <= game->larm1.s.c[0] + game->larm1.s.width &&
		     b->s.center.y < game->larm1.s.c[1] + game->larm1.s.height &&
		     b->s.center.y > game->larm1.s.c[1] - game->larm1.s.height)
		    ||
		    (b->s.center.x >= game->rarm2.s.c[0] - game->rarm2.s.width &&
		     b->s.center.x <= game->rarm2.s.c[0] + game->rarm2.s.width &&
		     b->s.center.y < game->rarm2.s.c[1] + game->rarm2.s.height &&
		     b->s.center.y > game->rarm2.s.c[1] - game->rarm2.s.height)
		    ||
		    (b->s.center.x >= game->larm2.s.c[0] - game->larm2.s.width &&
		     b->s.center.x <= game->larm2.s.c[0] + game->larm2.s.width &&
		     b->s.center.y < game->larm2.s.c[1] + game->larm2.s.height &&
		     b->s.center.y > game->larm2.s.c[1] - game->larm2.s.height)
		    ||
		    (b->s.center.x >= game->rleg1.s.c[0] - game->rleg1.s.width &&
		     b->s.center.x <= game->rleg1.s.c[0] + game->rleg1.s.width &&
		     b->s.center.y < game->rleg1.s.c[1] + game->rleg1.s.height &&
		     b->s.center.y > game->rleg1.s.c[1] - game->rleg1.s.height)
		    ||
		    (b->s.center.x >= game->rleg2.s.c[0] - game->rleg2.s.width &&
		     b->s.center.x <= game->rleg2.s.c[0] + game->rleg2.s.width &&
		     b->s.center.y < game->rleg2.s.c[1] + game->rleg2.s.height &&
		     b->s.center.y > game->rleg2.s.c[1] - game->rleg2.s.height)
		    ||
		    (b->s.center.x >= game->lleg1.s.c[0] - game->lleg1.s.width &&
		     b->s.center.x <= game->lleg1.s.c[0] + game->lleg1.s.width &&
		     b->s.center.y < game->lleg1.s.c[1] + game->lleg1.s.height &&
		     b->s.center.y > game->lleg1.s.c[1] - game->lleg1.s.height)
		    ||
		    (b->s.center.x >= game->lleg2.s.c[0] - game->lleg2.s.width &&
		     b->s.center.x <= game->lleg2.s.c[0] + game->lleg2.s.width &&
		     b->s.center.y < game->lleg2.s.c[1] + game->lleg2.s.height &&
		     b->s.center.y > game->lleg2.s.c[1] - game->lleg2.s.height))
		     {
			 p->s.rotInc += GRAVITY/4;
			 p->s.velocityx += 6;
			 deleteBlueBird(game, b);
			 //b->s.center.y += 100;
		     }
	    b = b->next;
	}

	/*

	   if(
	   (b2->s.center.x >= p->s.c[0] - p->s.width &&
	   b2->s.center.x <= p->s.c[0] + p->s.width &&
	   b2->s.center.y < p->s.c[1] + p->s.height &&
	   b2->s.center.y > p->s.c[1] - p->s.height)
	   ||
	   (b2->s.center.x >= game->head.s.c[0] - game->head.s.width &&
	   b2->s.center.x <= game->head.s.c[0] + game->head.s.width &&
	   b2->s.center.y < game->head.s.c[1] + game->head.s.height &&
	   b2->s.center.y > game->head.s.c[1] - game->head.s.height)
	   ||
	   (b2->s.center.x >= game->rarm1.s.c[0] - game->rarm1.s.width &&
	   b2->s.center.x <= game->rarm1.s.c[0] + game->rarm1.s.width &&
	   b2->s.center.y < game->rarm1.s.c[1] + game->rarm1.s.height &&
	   b2->s.center.y > game->rarm1.s.c[1] - game->rarm1.s.height)
	   ||
	   (b2->s.center.x >= game->larm1.s.c[0] - game->larm1.s.width &&
	   b2->s.center.x <= game->larm1.s.c[0] + game->larm1.s.width &&
	   b2->s.center.y < game->larm1.s.c[1] + game->larm1.s.height &&
	   b2->s.center.y > game->larm1.s.c[1] - game->larm1.s.height)
	   ||
	   (b2->s.center.x >= game->rarm2.s.c[0] - game->rarm2.s.width &&
	   b2->s.center.x <= game->rarm2.s.c[0] + game->rarm2.s.width &&
	   b2->s.center.y < game->rarm2.s.c[1] + game->rarm2.s.height &&
	   b2->s.center.y > game->rarm2.s.c[1] - game->rarm2.s.height)
	   ||
	   (b2->s.center.x >= game->larm2.s.c[0] - game->larm2.s.width &&
	   b2->s.center.x <= game->larm2.s.c[0] + game->larm2.s.width &&
	   b2->s.center.y < game->larm2.s.c[1] + game->larm2.s.height &&
	   b2->s.center.y > game->larm2.s.c[1] - game->larm2.s.height)
	   ||
	   (b2->s.center.x >= game->rleg1.s.c[0] - game->rleg1.s.width &&
	   b2->s.center.x <= game->rleg1.s.c[0] + game->rleg1.s.width &&
	   b2->s.center.y < game->rleg1.s.c[1] + game->rleg1.s.height &&
	   b2->s.center.y > game->rleg1.s.c[1] - game->rleg1.s.height)
	   ||
	   (b2->s.center.x >= game->rleg2.s.c[0] - game->rleg2.s.width &&
	   b2->s.center.x <= game->rleg2.s.c[0] + game->rleg2.s.width &&
	   b2->s.center.y < game->rleg2.s.c[1] + game->rleg2.s.height &&
	   b2->s.center.y > game->rleg2.s.c[1] - game->rleg2.s.height)
	   ||
	   (b2->s.center.x >= game->lleg1.s.c[0] - game->lleg1.s.width &&
	   b2->s.center.x <= game->lleg1.s.c[0] + game->lleg1.s.width &&
	   b2->s.center.y < game->lleg1.s.c[1] + game->lleg1.s.height &&
	   b2->s.center.y > game->lleg1.s.c[1] - game->lleg1.s.height)
	   ||
	   (b2->s.center.x >= game->lleg2.s.c[0] - game->lleg2.s.width &&
	   b2->s.center.x <= game->lleg2.s.c[0] + game->lleg2.s.width &&
	   b2->s.center.y < game->lleg2.s.c[1] + game->lleg2.s.height &&
	   b2->s.center.y > game->lleg2.s.c[1] - game->lleg2.s.height))
	   {
	   p->s.rotInc += -GRAVITY/4;
	   p->s.velocityx += -6;
	   b2->s.center.y += 100;
	   }
	   */
    }
}
