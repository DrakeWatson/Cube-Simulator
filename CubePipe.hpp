#ifndef CUBEPIPE_HPP
#define CUBEPIPE_HPP
#include <vector>
#include <memory>
#include "CubeCube.hpp"

using std::vector;
class Pipe
{

	private:
	int state;
	Cube* input;
	vector<Cube*> output;		
	public:
	Pipe();
	Pipe(const Pipe&);
	Pipe(int, Cube*, vector<Cube*>);
	int getState();
	string getStringState();
	void setState(int);
	Cube* getInput();
	void setInput(Cube*);
	vector<Cube*> getOutput();
	void setOutput(vector<Cube*>);
	

};

#endif
