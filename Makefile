all: cube

cube:	CubeIntersection.o CubePipe.o CubeCube.o CubeNetwork.o CubeMain.o 
	g++ CubeMain.o CubeNetwork.o CubeCube.o CubePipe.o CubeIntersection.o -o cubeOutput 	
	
CubeMain.o: CubeMain.cpp
	g++ -c CubeMain.cpp -std=c++11

CubeNetwork.o: CubeNetwork.cpp
	g++ -c CubeNetwork.cpp -std=c++11
	
CubeIntersection.o: CubeIntersection.cpp
	g++ -c CubeIntersection.cpp -std=c++11

CubeCube.o: CubeCube.cpp 
	g++ -c CubeCube.cpp -std=c++11

CubePipe.o: CubePipe.cpp
	g++ -c CubePipe.cpp -std=c++11

clean:
	rm -rf *o cube


