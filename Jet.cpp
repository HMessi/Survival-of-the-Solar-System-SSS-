#include "Jet.h"
#include "Fire.h"

Jet::Jet(double initx, double inity) : Element(initx,inity)
{
	dx = 0;
	dy = 0;
	health = 5;
}

void Jet::shoot(double _x, double _y, int hp)
{
    //To add bullets to the jet
	fire.push_back(Fire(_x,_y,hp));
}
