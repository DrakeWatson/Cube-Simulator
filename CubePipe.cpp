#include "CubePipe.hpp"
#include <string>

using std::string;	
Pipe::Pipe()
{
	state = 1;
	input = nullptr;
	output.push_back(nullptr);
}

Pipe::Pipe(int s, Cube* in, vector<Cube*> out)
{
	state = s;
	input = in;
	output = out;
}
Pipe::Pipe(const Pipe& p)
{
	state = p.state;
	input = p.input;
	output.clear();
	for(int i = 0; i < p.output.size(); i++)
	{
		output.push_back(p.output[i]);
	}
}

int Pipe::getState()
{
	return state;
}

string Pipe::getStringState()
{
	if(state == 1)
	{
		return "+";
	}
	else if(state == 2)
	{
		return "-";
	}
	else if(state == 3)
	{
		return "*";
	}
}

void Pipe::setState(int s)
{
	state = s;
}
Cube* Pipe::getInput()
{
	return input;
}

void Pipe::setInput(Cube* newInput)
{
	input = newInput;
}

vector<Cube*> Pipe::getOutput()
{
	return output;
}

void Pipe::setOutput(vector<Cube*> newOutput)
{
	output = newOutput;	
}
	
	
