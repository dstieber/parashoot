// Alexzander Burden
#include "alexA.h"

void DefineRagdoll(Game *game)
{
	Character *c;
	//define body shape
	c = &game->body;
	c->s.width = 28;
	c->s.height = 66;
	c->s.c[0] = c->s.width/2;
	c->s.c[1] = c->s.height/2;
	//place body
	c->s.c[0] += 300.0;
	c->s.c[1] += 50;
	c->s.color[1] = 90;
	c->s.color[1] = 0;
	c->s.color[2] = 90;
	c->s.rotInc = 0.0f;
	c->s.rot = 1.0f;
	identity33(c->s.m);
	//define upper right arm
	c = &game->rarm1;
	c->s.width = 10;
	c->s.height = 40;
	c->s.c[0] = c->s.width/2;
	c->s.c[1] = 0;
	//place on body
	c->s.c[0] += 15;
	c->s.c[1] += 20;
	c->s.color[0] = 0;
	c->s.color[1] = 0;
	c->s.color[2] = 0;
	c->s.rotInc = 0.0f;
	c->s.rot = 45.0f;
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
	c->s.color[0] = 45;
	c->s.color[1] = 90;
	c->s.color[2] = 45;
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
	c->s.c[0] += -25;
	c->s.c[1] += 20;
	c->s.color[0] = 0;
	c->s.color[1] = 0;
	c->s.color[2] = 0;
	c->s.rotInc = 0.0f;
	c->s.rot = 315.0f;
	identity33(c->s.m);
	//define lower left arm
	c = &game->larm2;
	c->s.width = 10;
	c->s.height = 40;
	c->s.c[0] = c->s.width/2;
	c->s.c[1] = 0;
	//place on upper arm
	c->s.c[0] += -3;
	c->s.c[1] += 30;
	c->s.color[0] = 45;
	c->s.color[1] = 90;
	c->s.color[2] = 45;
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
	c->s.c[0] += 13;
	c->s.c[1] += -20;
	c->s.color[0] = 90;
	c->s.color[1] = 45;
	c->s.color[2] = 45;
	c->s.rotInc = 0.0f;
	c->s.rot = 135.0f;
	identity33(c->s.m);
	//define right shin
	c = &game->rleg2;
	c->s.width = 10;
	c->s.height = 40;
	c->s.c[0] = c->s.width/2;
	c->s.c[1] = 0;
	//place shin on quad
	c->s.c[0] += 20;
	c->s.c[1] += 65;
	c->s.color[0] = 45;
	c->s.color[1] = 90;
	c->s.color[2] = 45;
	c->s.rotInc = 0.0f;
	c->s.rot = 225.0f;
	identity33(c->s.m);
	//define left quad
	c = &game->lleg1;
	c->s.width = 10;
	c->s.height = 45;
	c->s.c[0] = c->s.width/2;
	c->s.c[1] = 0;
	//place on body
	c->s.c[0] += -20;
	c->s.c[1] += -20;
	c->s.color[0] = 90;
	c->s.color[1] = 90;
	c->s.color[2] = 45;
	c->s.rotInc = 0.0f;
	c->s.rot = 225.0f;
	identity33(c->s.m);
	//define left shin
	c = &game->lleg2;
	c->s.width = 10;
	c->s.height = 40;
	c->s.c[0] = c->s.width/2;
	c->s.c[1] = 0;
	//place shin on quad
	c->s.c[0] += -30;
	c->s.c[1] += 70;
	c->s.color[0] = 45;
	c->s.color[1] = 90;
	c->s.color[2] = 45;
	c->s.rotInc = 0.0f;
	c->s.rot = 135.0f;
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
