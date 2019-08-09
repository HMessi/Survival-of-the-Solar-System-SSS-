#pragma once
#include "StdAfx.h"
#include "Element.h"
#include "Fire.h"

class Jet: public Element
{
public:
	Jet(double initx, double inity);

	void shoot(double _x, double _y, int hp);

	std::vector<Fire> fire;
};
