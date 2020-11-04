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
	//TODO: use int as a error tester, maybe add arguments to modify map creation
	//generates a map with a random start and end points and random obstacles
	//arguments:
	//	obsPercent: the percentage of squares that will be on average be obstacles (default value is 50%)
	//		must be between 0 and 1, anyhting less than 0 will be considered as 0% and anything greater than 1 will be 100%
	int generateMap(double obsPercent = 0.5);
	//returns what style of coordinate this is
	int getPointStatus(int x, int y);

};

#endif
