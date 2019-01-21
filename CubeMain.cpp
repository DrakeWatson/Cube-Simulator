#include <iostream>
#include "CubeCube.hpp"
#include "CubePipe.hpp"
#include "CubeNetwork.hpp"
using std::cout;
using std::cin;
using std::endl;
using std::string;
int main()
{
	cout << "1" << endl;
	Network test("c355", "$-c$+!c*!c+&");
	cout << "2" << endl;
	vector<Cube*> vCubeTest = test.getCubeVec();
	vector<Pipe*> vPipeTest = test.getPipeVec();
	cout << "3" << endl;
	for(int i = 0; i < vCubeTest.size(); i++)
	{
	cout << "4" << endl;
		cout << "Cube ID: " << vCubeTest[i]->getID() << " Cube Val: " << vCubeTest[i]->getVal() << " Cube State: " << vCubeTest[i]->getState() << " Interssection: " << vCubeTest[i]->isIntersection() << endl;
	}
	for(int i = 0; i < vPipeTest.size(); i++)
	{
		cout << i << endl;
		cout << "Pipe State: " << vPipeTest[i]->getState() << endl;
		cout << " Pipe input Cube ID: " << vPipeTest[i]->getInput()->getID() << endl;
		cout << " Pipe is coming from an intersecttion: " << vPipeTest[i]->getInput()->isIntersection() << endl;
	
	}	
	cout << "6" << endl;
	
	
}
