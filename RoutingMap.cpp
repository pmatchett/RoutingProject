#include "RoutingMap.h"
#include <ctime>

RoutingMap::RoutingMap(int x, int y) {
	xDim = x;
	yDim = y;
	positions.resize(yDim);
	for (int i = 0; i < yDim; i++) {
		positions[i].resize(xDim);
	}
}

int RoutingMap::generateMap() {
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
	int obstacle;
	for (int i = 0; i < xDim; i++) {
		for (int j = 0; j < yDim; j++) {
			if ((i == startX && j == startY) || (i == endX && j == endY)) {
				continue;
			}
			obstacle = rand() % 2;//this should be 0 or 1 
			positions[i][j] = obstacle;
		}
	}
	
	return 0;
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