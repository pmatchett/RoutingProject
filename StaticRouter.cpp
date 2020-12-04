#include "StaticRouter.h"
#include "framework.h"
#include <cstdio>

//This source file was originally designed by me and a group mate (Patrick and Matt Kadatdz) for the capstone project SAFE 
//and I am reusing most of the code with slight changes

StaticRouter::StaticRouter(RoutingMap* map)
{
	this->map = map;
	openList = std::vector<Node*>();
	closedList = std::vector<bool>();
	startPoint = nullptr;
	endPoint = nullptr;
}

//TODO: it feels like its checking too many nodes, but is still checking in the correct direction so it might be fine
int StaticRouter::optimizePath()
{
	//resetting the previous path so that it does not mess with the new one
	reset();
	setMapStartEnd();
	//making sure the start and end points are not within obstacles;
	if (startPoint->getStatus() == OBSTACLE || endPoint->getStatus() == OBSTACLE) {
		OutputDebugString(_T("The start or end points are invalid\n"));
		return 1;
	}
	OutputDebugString(_T("starting route creation\n"));
	//placing the start nod
	openList.push_back(startPoint);
	//while there is at least one node on the open list keep looking (this means there is atleast one path not yet explored)
	while (!openList.empty()) {
		//getting the node with the smallest distance heuristic (The index is used to track which element of the vector to remove
		Node* testNode = openList[0];
		int index = 0;
		for (uint8_t i = 0; i < openList.size(); i++) {
			if (openList[i]->getHeuristic() <= 0) {
				calculateDistance(openList[i]);
			}
			//if the node has a smaller distance travelled + distance to the end than the current lowest set it as the lowest
			if ((openList[i]->getDistanceTravelled() + openList[i]->getHeuristic()) < (testNode->getDistanceTravelled() + testNode->getHeuristic())) {
				testNode = openList[i];
				index = i;
			}
		}
		//at this point the next optimal node has been selected to investigate a path originating from it
		//removing the node we are investigating from the openList
		openList.erase(openList.begin() + index);
		//placing the node on the closed list so that it is not visited again
		closedList[testNode->getId()] = true;
		if (isEnd(testNode)) {
			tracePath();
			return 0;
		}
		//the end point has not been reached, so now we check the node's neighbours to find the next node of interest
		std::vector<Node*> neighbours = map->getNeighbours(testNode);
		//looping through all of the nieghbours and adding them to the open list, or changing the heuristics if a better path was found
		for (uint8_t i = 0; i < neighbours.size(); i++) {
			//skipping the node if it is already on the closed list (we have already visited it) or is an obstacle
			if (neighbours[i]->getStatus() == OBSTACLE || closedList[neighbours[i]->getId()]) {
				continue;
			}
			//if the node is already on the openList check if this new path is faster
			double newDistance = (testNode->getDistanceTravelled() + (neighbours[i]->euclideanDistance(testNode)));
			if (onOpen(neighbours[i])) {
				if (newDistance < neighbours[i]->getDistanceTravelled()) {
					neighbours[i]->setDistanceTravelled(newDistance);
					neighbours[i]->setPrev(testNode);
				}
			}
			else {
				neighbours[i]->setDistanceTravelled(newDistance);
				neighbours[i]->setPrev(testNode);
				openList.push_back(neighbours[i]);
			}
		}
	}

	return 1;
}

void StaticRouter::setStart(Node* start)
{
	startPoint = start;
}

void StaticRouter::setEnd(Node* end)
{
	endPoint = end;
}

bool StaticRouter::isEnd(Node* currentLocation)
{
	if (currentLocation->getStatus() == END) {
		return true;
	}
	else {
		return false;
	}
}

double StaticRouter::calculateDistance(Node* current)
{
	double distance = *current - endPoint;
	current->setDistanceWeight(distance);
	return distance;
}

bool StaticRouter::onOpen(Node* current)
{
	for (uint8_t i = 0; i < openList.size(); i++) {
		if (current->getId() == openList[i]->getId()) {
			return true;
		}
	}
	return false;
}

void StaticRouter::tracePath()
{
	//starting at the end point work back from previous node pointer to set all of the flags necessary
	Node* current = endPoint;
	Node* previous = nullptr;
	while (current != nullptr) {
		current->setIncluded(true);
		current->setNextNode(previous);
		previous = current;
		current = current->getPrev();
	}
}

void StaticRouter::reset()
{
	openList.clear();
	closedList.clear();
	//setting all nodes to not have been visited (the closed list is empty)
	for (int i = 0; i < map->getNumNodes(); i++) {
		closedList.push_back(false);
	}
}

bool StaticRouter::doubleCompare(double first, double second)
{
	return abs(first-second) < 0.00001;
}

void StaticRouter::setMapStartEnd()
{
	startPoint = map->getStart();
	endPoint = map->getEnd();
}




