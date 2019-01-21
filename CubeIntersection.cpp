#include "CubeIntersection.hpp"

Intersection::Intersection()
{
	val = 0;
	state = true;
	ID = "placeHolder";
	first = 0;
	second = 0;
	type = 0;
}
void Intersection::setType(int t)
{
	type = t;
}
void Intersection::setType(int firstPipe, int secondPipe) //Arbitrary type assignments based upon the two pipes that are connected to the intersection.
{
	if(firstPipe == secondPipe)//If both pipes are the same type.
	{
		if(firstPipe == 1)
		{
		type = 1;
		}
		else if(firstPipe == 2)
		{
		type = 5;
		}
		else if(firstPipe == 3)
		{
		type = 6;
		}
	}
	else if((firstPipe == 1 && secondPipe == 2) || (firstPipe == 2 && secondPipe == 1))
	{
		type = 2;
	}
	else if((firstPipe == 1 && secondPipe == 3) || (firstPipe == 3 && secondPipe == 1))
	{
		type = 3;
	}
	else if((firstPipe == 2 && secondPipe == 3) || (firstPipe == 3 && secondPipe == 2))
	{
		type = 4;
	}

}

bool Intersection::isIntersection()
{
	return true;
}

void Intersection::intersectionVal(int firstInput, int secondInput) //Cycle the inputs and ensure that the output is calculated based upon the type and the input values.
{
	first = firstInput;
	second = secondInput;
	
	if(type == 1)
	val = first + second;
	else if(type == 2)
	val = first / second;
	else if(type == 3)	
	val = first * second;		
	else if(type == 4)
	val = first;
	else if(type == 5)
	val = first - second;
	else if(type == 6)
	val = second;
}


	
