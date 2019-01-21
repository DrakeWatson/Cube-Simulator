#ifndef CUBEINTERSECTION_HPP
#define CUBEINTERSECTION_HPP
#include "CubeCube.hpp"

class Intersection: public Cube
{
	private:
	int first;
	int second; 	
	public:
	Intersection();
	void setType(int, int);
	void setType(int);
	bool isIntersection();
	void intersectionVal(int, int);
	

};

#endif
