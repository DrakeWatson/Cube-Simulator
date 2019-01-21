#ifndef CUBECUBE_HPP
#define CUBECUBE_HPP
#include <string>

using std::string;
class Cube
{

	protected:
	bool state;
	int val;
	int type;
	string ID;
	public:
	Cube();
	Cube(bool, int, string);
	bool getState();
	void setState(bool);
	virtual int getType();
	virtual int getVal();
	virtual void setVal(int);
	virtual string getID();
	virtual void setID(string);
	virtual bool isIntersection();

	

};
#endif
