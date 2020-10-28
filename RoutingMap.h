#pragma once
#ifndef ROUTINGMAPHEADER
#define ROUTINGMAPHEADER
#include <vector>
#define FREE 0 
#define OBSTACLE 1 
#define START 2 
#define END 3 

class RoutingMap {
private:
	int xDim, yDim;
	//each int represents a state: 0 = free, 1 = obstacle, 2 = start, 3 = end
	std::vector<std::vector<int>> positions;

public:
	RoutingMap(int x, int y);
	int getX();
	int getY();
	//use int as a error tester, maybe add arguments to modify map creation
	int generateMap();
	//returns what wtyle of coordinate this is
	int getPointStatus(int x, int y);

};

#endif
