#pragma once
#ifndef ROUTINGMAPHEADER
#define ROUTINGMAPHEADER
#include <vector>
#include "Node.h"


class RoutingMap {
private:
	int xDim, yDim, numNodes;

	Node* start, *end;
	
	std::vector<std::vector<Node*>> positions;
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
	//generates an empty map (no obstacles or start/end points)
	int generateEmpty();
	//returns what style of coordinate this is
	int getPointStatus(int x, int y);
	//Sets the status of a given point on the map
	void setPointStatus(int x, int y, int status);
	//returns if a point is included in the final route
	bool getPointIncluded(int x, int y);
	//returns the number of nodes that are currently in the map
	int getNumNodes();
	//returns a vector with all of the nodes adjacent to the argument node
	std::vector<Node*> getNeighbours(Node* center);

	Node* getEnd();

	Node* getStart();

	//the set start and end functions will only work if the start or end are not yet defined (used for empy maps)
	void setStart(int x, int y);
	void setEnd(int x, int y);

};

#endif
