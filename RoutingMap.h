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
	//removes all elements from the positions vector
	void deleteMap();

public:
	//creates a map with the x and y dimensions specified
	RoutingMap(int x, int y);
	//gets the x dimension
	int getX();
	//gets the y dimension
	int getY();
	//use int as a error tester, maybe add arguments to modify map creation
	//generates a map with a random start and end points and random obstacles
	//TODO: allow an argument that specifies likelihood of obstacles, so its not always 50/50 (set a default value)
	int generateMap();
	//returns what style of coordinate this is
	int getPointStatus(int x, int y);

};

#endif
