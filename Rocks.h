#pragma once
#include "StdAfx.h"
#include "Element.h"
#include "Fire.h"

class Rocks : public Element
{
public:
	Rocks(double initx, double inity, int r);

	int radius;
	void shoot(double _x, double _y, int hp);

	std::vector<Fire> fire;
};
