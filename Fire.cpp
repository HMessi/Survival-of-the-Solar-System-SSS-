#include "Fire.h"

Fire::Fire(double initx, double inity, int hp) : Element(initx,inity)
{
	dx = 20;
	dy = 0;
	health = hp;
}
