#include "CubeCube.hpp"

Cube::Cube()
{
	state = true;
	val = 0;
	ID = "";
	type = 0;
}

Cube::Cube(bool s, int v, string i)
{
	state = s;
	val = v;
	ID = i;
	type = 0;
}

bool Cube::getState()
{
	return state;
}

void Cube::setState(bool s)
{
	state = s;
}
int Cube::getType()
{
	return type;
}

int Cube::getVal()
{
	return val;
}

void Cube::setVal(int v)
{
	val = v;
}

string Cube::getID()
{
	return ID;
}

void Cube::setID(string i)
{
	ID = i;
}

bool Cube::isIntersection()
{
	return false;
}
