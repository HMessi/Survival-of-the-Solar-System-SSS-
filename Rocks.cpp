#include "Rocks.h"
#include "Fire.h"

Rocks::Rocks(double initx, double inity, int r) : Element(initx,inity)
{
	radius = r;
	dx = (rand()%3)-3;
	dy = (rand()%3)-1;
	health = 4 + dx;
}


