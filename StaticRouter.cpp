#include "StaticRouter.h"
#include "framework.h"

StaticRouter::StaticRouter(RoutingMap* map)
{
	this->map = map;
	openList = std::vector<Node*>();
	closedList = std::vector<bool>();
	startPoint = nullptr;
	endPoint = nullptr;
}

int StaticRouter::optimizePath()
{
	//resetting the previous path so that it does not mess with the new one
	reset();
	//making sure the start and end points are not within obstacles;
	if (startPoint->getStatus() == OBSTACLE || endPoint->getStatus() == OBSTACLE) {
		OutputDebugString(_T("The start or end points are invalid\n"));
		return 1;
	}

	return 0;
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
	return distance;
}

bool StaticRouter::onOpen(Node* current)
{
	return false;
}

void StaticRouter::tracePath()
{
}

void StaticRouter::reset()
{
	openList.clear();
	closedList.clear();
}

bool StaticRouter::doubleCompare(double first, double second)
{
	return abs(first-second) < 0.00001;
}




