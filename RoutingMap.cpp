#include "RoutingMap.h"
#include <ctime>
#include "framework.h"

RoutingMap::RoutingMap(int x, int y) {
	xDim = x;
	yDim = y;
	numNodes = x * y;
	start = nullptr;
	end = nullptr;
}

int RoutingMap::generateMap(double obsPercent) {
	//deleting any previously existing map
	deleteMap();
	//setting the vector to the correct length
	positions.resize(yDim);
	for (int i = 0; i < yDim; i++) {
		positions[i].resize(xDim);
	}
	//seeding rand with the current time on the machine
	srand((uint16_t)std::time(nullptr));
	//select the starting and ending point
	int startX = rand() % xDim;
	int startY = rand() % yDim;
	int endX, endY;
	do {
		endX = rand() % xDim;
		endY = rand() % yDim; 
	} while (endX == startX && endY == startY);
	//generating what type of point each sqaure will be
	int obstacle;
	for (int i = 0; i < xDim; i++) {
		for (int j = 0; j < yDim; j++) {
			if (i == startX && j == startY)  {
				positions[i][j] = new Node(i, j, START);
				start = positions[i][j];
			}
			else if ((i == endX && j == endY)) {
				positions[i][j] = new Node(i, j, END);
				end = positions[i][j];
			}
			else {
				obstacle = (rand() % 100) + 1;//this should be between 1 and 100 
				//if the random value is less than the value specified for the obstacle percent set the sqaure as an obstacle
				if (obstacle <= obsPercent * 100) {
					positions[i][j] = new Node(i,j,OBSTACLE);
				}
				else {
					positions[i][j] = new Node(i,j,FREE);
				}
			}
		}
	}
	return 0;
}

int RoutingMap::generateEmpty() {
	//deleting any previously existing map
	deleteMap();
	//setting the vector to the correct length
	positions.resize(yDim);
	for (int i = 0; i < yDim; i++) {
		positions[i].resize(xDim);
	}
	for (int i = 0; i < xDim; i++) {
		for (int j = 0; j < yDim; j++) {
			positions[i][j] = new Node(i, j, FREE);
		}
	}
	start = nullptr;
	end = nullptr;
	return 0;
}

//TODO: might need to fix this function to work with pointers
void RoutingMap::deleteMap() {
	for (uint8_t i = 0; i < positions.size(); i++) {
		positions[i].erase(positions[i].begin(), positions[i].end());
	}
	positions.erase(positions.begin(), positions.end());
	Node::resetCounter();
}

int RoutingMap::getNumNodes() {
	return numNodes;
}

//TODO: should diagonals be allowed
std::vector<Node*> RoutingMap::getNeighbours(Node* center)
{
	std::vector<Node*> neighbours;
	int x = center->getxCoord();
	int y = center->getyCoord();
	for (int i = x - 1; i <= x + 1; i++) {
		for (int j = y - 1; j <= y + 1; j++) {
			//do not add nodes that are outside the boundaries of the map or the current Node
			if (i < 0 || i >= xDim || j < 0 || j >= yDim || (i == x && j == y)) {
				continue;
			}
			neighbours.push_back(positions[i][j]);
		}
	}return neighbours;
}

Node* RoutingMap::getEnd()
{
	return end;
}

Node* RoutingMap::getStart()
{
	return start;
}

int RoutingMap::getPointStatus(int x, int y){
	return positions[x][y]->getStatus();
}

void RoutingMap::setPointStatus(int x, int y, int status)
{
	positions[x][y]->setStatus(status);
}

bool RoutingMap::getPointIncluded(int x, int y) {
	return positions[x][y]->getIncluded();
}


int RoutingMap::getX() {
	return xDim;
}

int RoutingMap::getY() {
	return yDim;
}

void RoutingMap::setStart(int x, int y) {
	if (start != nullptr) {
		return;
	}
	start = positions[x][y];
	start->setStatus(START);
}

void RoutingMap::setEnd(int x, int y) {
	if (end != nullptr) {
		return;
	}
	end = positions[x][y];
	end->setStatus(END);
}