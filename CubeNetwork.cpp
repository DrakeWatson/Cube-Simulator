#include "CubeNetwork.hpp"
#include <iostream>

using std::cout;
using std::endl;

Network::Network()
{
	name = "";
	description = "";
	out = 0;
}

Network::Network(string n, string d)
{
	name = n;
	description = d;
	out = 0;
	generateCubes();
	cout << "Generated cubes succesfully. Moving to pipes.\n\n\n\n\n\n\n\n" << endl;
	generatePipes();
	cout << "Generated pipes succesfully." << endl;
	squashPipes();
	cout << "Squashed pipes succesfully." << endl;


}
void Network::generateCubes()
{	
	for(int i = 0; i < name.length(); i++) //Load the cubes into memory.
	{
		if(isalpha(name[i]))	//If the character we are at is a letter, then:
		{
			cout << "Found an alpha character at i:" << i << endl;
			if(islower(name[i]))	//If the character we are at is lowercase, then:
			{
				cout << "Found a lowercase character at i:" << i << endl;
				int endPlace = 0; //This will hold the location of the end of this Cube's value.
				for(int j = i + 1; j < name.length() + 1; j++) //Find how large the value of the cube is.
				{
					if(j == name.length()) //If we reach the end of the string.
					{
						cout << "Reached the end of the string. Currently at: " << endPlace << endl;
						endPlace = j - 1;
					}

					else if(!(isalpha(name[j])))//If this is a number, keep going.
					{
						cout << "Adding to the length of the number. Currently at : " << endPlace << endl;
						endPlace++;
					}
					else if(isalpha(name[j]))//If we find a letter, stop.
					{
						cout << "Found another letter, stopping. Currently at: " << endPlace << endl;
						endPlace = j-1;
						j = name.length() + 1;
					}
					else
						throw string("Character was not alpha or int.");	
				}
				string toConvert = "";
				for(int k = 0; k <= (endPlace-(i + 1)); k++) //Get the value of the cube.
				{
					toConvert.push_back(name.at(k + i + 1));
				}
				cout << "About to allocate Memory. Cube Data- State: " << false << " Val: " << std::stoi(toConvert, nullptr) << " ID: " << name.substr(i,1) << endl;
				Cube* placeHolder = new Cube(false, std::stoi(toConvert, nullptr), name.substr(i,1)); //Allocate the memory.
				vCube.push_back(placeHolder);
				cout << "Succesfully allocated memory for cube at i: " << i << endl;

			}
			if(isupper(name[i]))	//If the character we are at is uppercase, then:

			{
				int endPlace; //This will hold the location of the end of this Cube's value.
				for(int j = i + 1; j < name.length() + 1; j++) //Find how large the value of the cube is.
				{
					if(j == name.length()) //If we reach the end of the string.
					{
						endPlace = j - 1;
					}
					else if(!(isalpha(name[j])))//If this is a number, keep going.
						endPlace++;

					else if(isalpha(name[j]))//If we find a letter, stop.
					{
						endPlace = j-1;
						j = name.length() + 1;
					}
					else
						throw string("Character was not alpha or int.");	
				}
				string toConvert = "";
				for(int k = 0; k <= (endPlace-(i + 1)); k++) //Get the value of the cube.
				{
					toConvert.push_back(name.at(k + i + 1));
				}

				Cube* placeHolder = new Cube(true, std::stoi(toConvert, nullptr), name.substr(i,1)); //Allocate the memory.
				vCube.push_back(placeHolder);

			}

		}

	}
		vector<Cube*>::iterator cubeIt;
		cubeIt = vCube.begin();
		Cube* startCube = new Cube(true, 0, "$"); //Create the starting cube and place it at the beggining of the cube vector.
		vCube.insert(cubeIt, 1, startCube);
	
	
}
int Network::convertType(string typeString)//Helper function for converting the string pipe-types into integer pipe-types.
{
	if(typeString == "+")
	{
		return 1;
	}
	else if(typeString == "-")
	{
		return 2;
	}
	else if(typeString == "*")
	{
		return 3;
	}
}
int Network::convertIntersect(string firstString, string secondString)//Helper function for determining what the intersection types are.
{
	if(firstString == secondString)
	{
		return convertType(firstString);
	}
	else if((firstString == "+" && secondString == "-") || (firstString == "-" && secondString == "+"))
	{
		return 3;
	}
	else if((firstString == "+" && secondString == "*") || (firstString == "*" && secondString == "+"))
	{
		return 2;
	}
	else if((firstString == "-" && secondString == "*") || (firstString == "*" && secondString == "-"))
	{
		return 1;
	}

}

void Network::generatePipes()
{	

	for(int i = 0; i < description.length(); i++)//Generate the pipes.
	{
		vector<Cube*> tempOutputs; //A temporary vector for holding the output values of the pipes.

		if(description[i] == '$' && !pipeExists(description.substr(i, 2)))//If this pipe is the input pipe. (The initial pipe, which will have no cube as its input)
		{
			cout << "Found the input pipe at i: " << i << endl;
			for(int j = i; j < description.length(); j++)//Find the rest of the input pipe's descriptions.
			{
				if(description[j] == '$' && (description[j + 1] == description[i + 1])) //If we find another description of the input pipe of the same type.
				{
					cout << "Found an input pipe description at j: " << j << endl;
					if(description[j+2] == '!' && !(checkForIntersection(description.substr(j,6))) && description[j+5] != '!')//If the description is a simple intersection (EX: x+!b+L) and this intersection has not been created yet, we must create a new intersection.	
					{
						simpleIntersection(j, tempOutputs);
					}
					else if(description[j+2] == '!' && description[j+5] == '!') //If the intersection is complex. EX: (x+!b+!f+l)
					{
						complexIntersection(j, tempOutputs);//Run the complex intersection function to create it.
						
						
					}
		
					else if(description[j+2] == '!') //If its a simple intersection that has been created already. Since we already checked that this intersection was created we don't need to check again.
					{	
						cout << "Intersection has already been made. Adding to pipe's output vector at j: " << j << endl;
						tempOutputs.push_back(findCube(description.substr(j,6))); //Add this intersection to our pipe's output vector.
					}	

					else//If the description is a normal cube ID.
					{
						cout << "Description is for a normal cube ID. Adding to pipe's output vector at j: " << j << endl;
						tempOutputs.push_back(findCube(description.substr(j+2,1))); //Add that cube to this pipe's output vector.
			
					}
		
				}
			}
			cout << "Making the new pipe. i: " << i << endl;
			Pipe* placeHolder = new Pipe(convertType(description.substr(i+1,1)), findCube("$"), tempOutputs); //Create the pipe.
			vPipe.push_back(placeHolder); //Store the pipe in the pipe vector.	
		}
		
		else if(isalpha(description[i]) && !(isalpha(description[i+1])) && (description[i-1] != '!') && !pipeExists(description.substr(i,2)) && description[i+1] != '$') //If we find the start of a new pipe. (IE. in the description $+GG+CC+!C-EE&, +GG is not a pipe, !C- is not a pipe, but G+C is a pipe.
		{
			cout << "Found the start of a new pipe at i : " << i << " Description around this point is: " << description.substr(i-1,3) << endl;
			if(description[i+1] == '&')//If we're at the end of the description, then this pipe will have no outputs.
			{
				cout << "Found the end of the description at i: " << i << endl;
				Pipe* placeHolder = new Pipe(1,findCube(description.substr(i,1)), tempOutputs);
				cout << "Pushing the last pipe to the vector." << endl;
				vPipe.push_back(placeHolder);
				i = description.length() + 1;
			}
			else
			{	
				for(int j = i; j < description.length(); j++)
				{
					if(description[j] == description[i] && description[j+1] == description[i+1]) //If we find a description of a pipe with the same type and input cube.
					{
						cout << "Found a description of a pipe with the same type and input cube at j: " << j << endl;
						
						if(description[j+2] == '!' && !(checkForIntersection(description.substr(j,6))) && description[j+5] != '!' && description[j-1] != '!')//If the description is a simple intersection (EX: x+!b+L) and this intersection has not been created yet, we must create a new intersection.
						{
							simpleIntersection(j, tempOutputs); //Run the simple intersection function to create it.
			
						}
						else if(description[j+2] == '!' && description[j+5] == '!') //If the intersection is complex. EX: (x+!b+!f+l)
						{
							complexIntersection(j, tempOutputs);//Run the complex intersection function to create it.
						
						
						}
						else if(description[j+2] == '!') //Since we already checked that this intersection was created we don't need to check again.
						{
							cout << "The intersection has already been made. Adding to output vector at j: " << j << endl;
							tempOutputs.push_back(findCube(description.substr(j,6))); //Add this intersection to our pipe's output vector.
						}
						else //If the description is a normal cube ID.
						{
							cout << "The description is being added to the pipe's output vector at j: " << j << endl;	
							tempOutputs.push_back(findCube(description.substr(j+2,1))); //Add that cube to this pipe's output vector.
						}
					}
					
				}
			
			cout << "Creating the new pipe and storing the output vector into it at i: " << i << endl;
			Pipe* placeHolder = new Pipe(convertType(description.substr(i+1,1)), findCube(description.substr(i,1)), tempOutputs);
			vPipe.push_back(placeHolder); //Store the pipe in the pipe vector.
			}
		}	
		tempOutputs.clear();	//Clear the temporary vector after each iteration of this loop.
		
			
	}

}
/*Simple Intersection Visualization: X+!c-b
 *
 *	1.	
 *	X+++|-  3. 	
 *          | -***b
 *	c---|-
 *	2.
 */
void Network::simpleIntersection(int j, vector<Cube*> &tempVec) 
{
	cout << "The description is an intersection that has not been created. Creating one at j: " << j << endl;
	Intersection* tempInter = new Intersection();//Allocate the memory and create the intersection.
	tempInter->setID(description.substr(j,6)); //Name the intersection.
	tempInter->setType(convertType(description.substr(j+1,1)), convertType(description.substr(j+4,1))); //Set the intersection's type.	
	tempVec.push_back(tempInter); //Add this intersection to this pipe's output vector. This will correspond with pipe 1. in the above visualization.
						
	vCube.push_back(tempInter); //Add this intersection to the network's cube vector.
	vector<Cube*> tempCube; //Since we are creating pipes inside of this function we no longer want to alter tempVec in order to create these ones.
 
	//Because an intersection has three pipes connected to it, we must create two additional pipes within this function.
	tempCube.push_back(findCube(description.substr(j,6)));
	Pipe* placeHolderOne = new Pipe(convertType(description.substr(j+4,1)), findCube(description.substr(j+3,1)), tempCube); //Pipe 3.
	tempCube.clear();
	tempCube.push_back(findCube(description.substr(j + 5, 1)));
	Pipe* placeHolderTwo = new Pipe(convertIntersect(description.substr(j+1,1),description.substr(j+4,1)),findCube(description.substr(j,6)), tempCube); //Pipe 2. 
	vPipe.push_back(placeHolderOne);
	vPipe.push_back(placeHolderTwo);



}
//Complex intersections have descriptions like b+!c-!x*!c+!b-x.
void Network::complexIntersection(int j, vector<Cube*> &tempVec)
{
	cout << "Found a complex intersection at j: " << j << endl;
	int size = 0; //The size of the complex intersection.
	for(int i = j; i < description.length(); i = i+3) //Determine the size of the complex intersection.
	{
		cout << "Finding the size of the intersection. i : " << i << endl;
		if(description[i + 2] == '!')
		{
		cout << "Increasing size." << endl;
		size++;
		}
		else
		{
		cout << "Stopping loop. " << endl;
		i = description.length();
		}
	} 
	cout << "Found size to be : " << size << endl;
	for(int h = size; h > 0; h--) //Create all of the intersections.
	{
		cout << "Creating all of the intersections at j: " << j << endl;
		Intersection* tempInter = new Intersection(); //Create an intersection for each one found in the complex intersection.
		cout << "CREATE DEBUG 1 " << endl;
		tempInter->setID(description.substr(j, (h * 3))); //Name the intersection.
		cout << "CREATE DEBUG 2 setting name to " << tempInter->getID() << endl;
		tempInter->setType(complexType(description.substr(j,(h * 3) + 1))); //Set the intersection's type.
		cout << "CREATE DEBUG 3 " << endl;
		vCube.push_back(tempInter); //Add the intersection to the cube vector.
		cout << "CREATE DEBUG 4 " << endl;
	}
	cout << "Creation complete." << endl;

	//Create the first two pipes.
	//First Pipe.
	vector<Cube*> tempCube; //Dummy vector to place into our pipe's output.
	tempVec.push_back(findCube(description.substr(j, 5))); //Add the intersection to our vector that will become the pipe outside of this function.
			
	//Second Pipe.
	Pipe* placeHolderTwo = new Pipe(convertType(description.substr(j+4,1)), findCube(description.substr(j+3,1)), tempCube);
	vPipe.push_back(placeHolderTwo);//Add our seconds pipe to our pipe vector.

	cout << "First two pipes completed. Moving onto procedural generation of inbatween pipes." << endl;
	for(int x = size; x > 1; x--) //Create all of the pipes.
	{
		cout << "Creating rest of the pipes." << endl;
		tempCube.clear();
		if(description[j + (x * 3) + 2] != '!') //Find the end of the complex intersection.
		{
			cout << "Found the end of a complex intersection." << endl;
			tempCube.push_back(findCube(description.substr(j + (x * 3) + 2, 1)));
			cout << "DEBUG 1" << endl;
			Pipe* placeHolderThree = new Pipe(findCube(description.substr(j, j + (x * 3) + 2))->getType(), findCube(description.substr(j, j + (x * 3) + 2)), tempCube);
			cout << "DEBUG 2" << endl;
			vPipe.push_back(placeHolderThree);
		}
		else
		{
		
			tempCube.push_back(findCube(description.substr(j, j + (x * 3) + 1))); //Add the intersection after this one to the dummy output vector.
			//Create the first pipe.
			Pipe* placeHolderFour = new Pipe(findCube(description.substr(j, j + ((x - 1) * 3) + 1))->getType(), findCube(description.substr(j, j + ((x-1) * 3) + 1)), tempCube);
			//Create the second pipe.
			Pipe* placeHolderFive = new Pipe(convertType(description.substr((j + (x * 3) + 2), 1)), findCube(description.substr((j + (x * 3) + 1), 1)), tempCube);
			//Add the pipes to the vector.
			vPipe.push_back(placeHolderFour);
			vPipe.push_back(placeHolderFive);	
		}
				

	}

			
			
		
		
		
	

}
int Network::complexType(string toSolve) //Helper function for recursive complexType function.
{	
	cout << "Running Complex Type check on " << toSolve << endl;
	string solved = complexTypeR(toSolve);
	if(solved[1] == '+')
	{
		cout << "Returning complex type of 1." << endl;
		return 1;
	}
	else if(solved[1] == '-')
	{
		cout << "Returning complex type of 2." << endl;
		return 2;
	}
	else if(solved[1] == '*')
	{
		cout << "Returning complex type of 3." << endl;
		return 3;
	}
	else return 0;	
	
}
string Network::complexTypeR(string toSolve)//Recursively find the type of a complex intersection.
{
	cout << "Running recursive function on string: " << toSolve << endl;
	string dummy = "";
	if(toSolve.length() <= 3) //Base case.
	{
		cout << "COMPLEX TYPE - HIT BASE CASE" << endl;
		return toSolve;
	}
	
	else if((toSolve[1] == '+' && toSolve[4] == '*') || (toSolve[4] == '+' && toSolve[1] == '*')) //+ and * gives -
	{
		if(toSolve.length() > 5)
		{
			dummy = "A-" + toSolve.substr(5, toSolve.length() - 5);
			return complexTypeR(dummy);
		}
		else
		{
			dummy = "A-";
			return complexTypeR(dummy);
		}
	}

	else if((toSolve[1] == '-' && toSolve[4] == '*') || (toSolve[4] == '-' && toSolve[1] == '*')) //- and * gives +
	{
		if(toSolve.length() > 5)
		{
			dummy = "A+" + toSolve.substr(5, toSolve.length() - 5);
			return complexTypeR(dummy);
		}
		else
		{
			dummy = "A+";
			return complexTypeR(dummy);
		}
	}

	else if((toSolve[1] == '+' && toSolve[4] == '-') || (toSolve[4] == '+' && toSolve[1] == '-')) //+ and - gives +
	{
		if(toSolve.length() > 5)
		{
			dummy = "A*" + toSolve.substr(5, toSolve.length() - 5);
			return complexTypeR(dummy);
		}
		else
		{
			dummy = "A*";
			return complexTypeR(dummy);
		}
	}	
	else
	{
		return complexTypeR(toSolve.substr(0, toSolve.length() - 2));	
		cout << "Recursive compleTypeR failed to find a combination." << endl;
	}

}
void Network::squashPipes()//A function that finds any repeated pipes and turns them into a single pipe.
{
	vector<Pipe*> vPipeTemp;
	vector<Pipe*>::iterator iIt = vPipe.begin();
	for(int i = 0; i < vPipe.size(); i++)
	{
		//Create a dummy bool to know if we've found any copies of this pipe.
		bool dupeFound = false;
		//Find the pipe ID and type at this location I.
		string pipeIDandType = vPipe[i]->getInput()->getID();
		pipeIDandType += vPipe[i]->getStringState();
		//Create an iterator to properly use .erase with vector.
		vector<Pipe*>::iterator jIt = vPipe.begin();
		//Create a temporary cube vector in order to combine the outputs of both pipes.
		vector<Cube*> tempCubeVec = vPipe[i]->getOutput();
		cout << "Searching for copies of this pipe at i: " << i << " pipeIDandType: " << pipeIDandType << endl;	
		for(int j = 0; j < vPipe.size(); j++)
		{	
			//Find the pipe ID and Type at this location J.
			string comparePipeIDandType = vPipe[j]->getInput()->getID();
			comparePipeIDandType += vPipe[j]->getStringState();
			cout << "j: " << j << " comparePipeIdandType: " << comparePipeIDandType << endl;
			if(i != j && comparePipeIDandType == pipeIDandType)//If we're not at the same pipe but they share the same input ID and type.
			{
				cout << "Found a pipe that has the same ID and type. " << endl;
				vector<Cube*> temp = vPipe[j]->getOutput();
				tempCubeVec.insert(tempCubeVec.end(),temp.begin(),temp.end());//Get all of the outputs of this vector.
				cout << "Deleting the copy." << endl; 
				delete vPipe[j]; //Delete the copy.
				cout << "Making the vector smaller." << endl;
				vPipe.erase(jIt);//Make the vector smaller.
				cout << "Running misc adjustments." << endl;
				j = j-1;
				 //Since we are deleting a piece of the vector, we must adjust our for loop accordingly.
				jIt++;
				dupeFound = true;
			}			
			jIt++;	
		}
		if(dupeFound == true)
		{
			cout << "Found a dupe(s). Erasing this pipe from the original vector temporarily. " << endl;
			vPipe[i]->setOutput(tempCubeVec); //Assign all of the copies' outputs to this pipe.
			cout << "Adding this pipe to the squashed pipes vector." << endl;
			vPipeTemp.push_back(vPipe[i]);//Add this pipe to the squashed pipes vector.
			cout << "Erasing this pipe's pointer from the vector. " << endl;
			vPipe.erase(iIt); //Erase this pipe's pointer from the vector.
			i = i-1;
		}
		iIt++;
		
	}
	vPipe.insert(vPipe.end(), vPipeTemp.begin(), vPipeTemp.end()); //Add the squashed pipes to the pipe vector.
		
	
	
}

bool Network::checkForIntersection(string interID)//Determine if an intersection has already been created or not.
{
	for(int i = 0; i < vCube.size(); i++)
	{
		if(vCube[i]->getID() == interID)
		{
			return true;
		}
	}
	return false;
}
bool Network::pipeExists(string cubeIDandType) //Determine if a pipe already exists by comparing input and type flags.
{
	//cout << "Checking if pipe exists. CubeID and Type: " << cubeIDandType << endl;
	if(isalpha(cubeIDandType[0]) && ispunct(cubeIDandType[1])) //If the input parameter for this function is garbage data from between pipe descriptions, throw it out.
	{

		for(int i = 0; i < vPipe.size(); i++)
		{
			if((vPipe[i]->getInput()) == findCube(cubeIDandType.substr(0,1)) && vPipe[i]->getState() == convertType(cubeIDandType.substr(1,1)))
			{
			//cout << "Pipe exists." << endl;
			return true;
			}
		}
	}
	else if(cubeIDandType[0] == '$')
	{
		for(int i = 0; i < vPipe.size(); i++)
		{
	
			if(vPipe[i]->getState() == convertType(cubeIDandType.substr(1,1)))
			{
			//cout << "Pipe exists." << endl;
			return true;
			}
		}
	}
	
	//cout << "Pipe does not exist." << endl;
	return false;

}
Network::Network(const Network &n)
{
	
}
Network::~Network()
{
	for(int i = 0; i < vCube.size(); i++)
	{
		delete vCube[i];
	}
	vCube.clear();
	for(int j = 0; j < vPipe.size(); j++)
	{
		delete vPipe[j];
	}
	vPipe.clear();
}

void Network::setName(string s)
{
	name = s;
}
vector<Cube*> Network::getCubeVec()
{
	return vCube;
}
vector<Pipe*> Network::getPipeVec()
{
	return vPipe;
}

string Network::getName()
{
	return name;
}

void Network::setDescription(string d)
{
	description = d;
}

string Network::getDescription()
{
	return description;
}

int Network::getOutput()
{
	return out;
}

Cube* Network::findCube(string LookingForID) //Given an ID, find a cube in the vCube vector.
{
	cout << "Executing findCube. Looking for ID: " << LookingForID << endl;
	for(int i = 0; i < vCube.size(); i++)
	{
		if(vCube[i]->getID() == LookingForID)
		{
			cout << "Found cube at i: " << i << endl;
			return vCube[i];
		}
	}
	cout << "Did not find cube." << endl;
	Cube* empty = nullptr;
	return empty;
}

int Network::input(int in) //Run this input through this cube network.
{
			
}



int Network::runCombination(int first, int second, string function) //Given two integers, use the function on both of them and produce the result.
{
	
	if(function == "+")
	{
		return first + second;
	}

	else if(function == "*")
	{
		return first * second;
	}
	else if(function == "-")
	{
		return first - second;
	}
	else if(function.length() > 1) //If this is an intersection combination.
	{
		if(function.substr(0, 1) == function.substr(2,1)) //If the intersection is taking in two of the same function types.
		{
			if(function.substr(0,1) != "*")
			return runCombination(first,second, function.substr(0,1)); 
			else return second;
		}
		else if((function.substr(0,1) == "+" && function.substr(2,1) == "*") || (function.substr(0,1) == "*" && function.substr(2,1) == "+"))//If the two functions are * and +.
		{
			return first * second;
		}
		else if((function.substr(0,1) == "-" && function.substr(2,1) == "*") || (function.substr(0,1) == "*" && function.substr(2,1) == "-"))//If the two functions are * and -.
		{
			return first; 
		}
		else if((function.substr(0,1) == "-" && function.substr(2,1) == "+") || (function.substr(0,1) == "+" && function.substr(2,1) == "-"))//If the two functions are + and -.
		{
			return first / second; 
		}

	}


}

