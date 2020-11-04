#include "RoutingMap.h"
#include <ctime>
#include "framework.h"

RoutingMap::RoutingMap(int x, int y) {
	xDim = x;
	yDim = y;
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
	srand(std::time(nullptr));
	//select the starting and ending point
	int startX = rand() % xDim;
	int startY = rand() % yDim;
	int endX, endY;
	do {
		endX = rand() % xDim;
		endY = rand() % yDim; 
	} while (endX == startX && endY == startY);
	positions[startX][startY] = START;
	positions[endX][endY] = END;
	//generating what type of point each sqaure will be
	int obstacle;
	for (int i = 0; i < xDim; i++) {
		for (int j = 0; j < yDim; j++) {
			if ((i == startX && j == startY) || (i == endX && j == endY)) {
				continue;
			}
			obstacle = (rand() % 100)+1;//this should be between 1 and 100 
			//if the random value is less than the value specified for the obstacle percent set the sqaure as an obstacle
			if (obstacle <= obsPercent * 100) {
				positions[i][j] = 1;
			}
			else {
				positions[i][j] = 0;
			}
		}
	}
	return 0;
}

void RoutingMap::deleteMap() {
	for (int i = 0; i < positions.size(); i++) {
		positions[i].erase(positions[i].begin(), positions[i].end());
	}
	positions.erase(positions.begin(), positions.end());
}

int RoutingMap::getPointStatus(int x, int y){
	return positions[x][y];
}

int RoutingMap::getX() {
	return xDim;
}

int RoutingMap::getY() {
	return yDim;
}