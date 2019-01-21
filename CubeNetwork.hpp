#ifndef CUBENETWORK_HPP
#define CUBENETWORK_HPP
#include <string>
#include "CubeCube.hpp"
#include "CubePipe.hpp"
#include "CubeIntersection.hpp"
#include <vector>
#include <ctype.h>
#include <stdio.h>
using std::string;
using std::stoi;
using std::vector;
class Network
{
	private:
	string name;
	string description;
	int out;
	vector<Cube*> vCube;
	vector<Pipe*> vPipe;
	Cube* findCube(string);
	int runCombination(int, int, string);
	void generateCubes();
	void generatePipes();
	int convertType(string);
	int convertIntersect(string, string);
	bool checkForIntersection(string);
	bool pipeExists(string);
	void squashPipes();
	void simpleIntersection(int, vector<Cube*>&);
	void complexIntersection(int, vector<Cube*>&);
	int complexType(string);
	string complexTypeR(string);
	public:
	Network();
	Network(const Network&);
	~Network();
	Network(string, string);
	void setName(string);
	string getName();
	void setDescription(string);
	string getDescription();
	int input(int);
	int getOutput();
	vector<Cube*> getCubeVec();
	vector<Pipe*> getPipeVec();
	


};
#endif
