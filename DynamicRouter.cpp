#include "DynamicRouter.h"
#include "framework.h" // this is only used until I can get multiple threads to track movement

void DynamicRouter::updateVisible()
{
	for (int i = currentLocation->getxCoord() - visibleRange; i <= currentLocation->getxCoord() + visibleRange; i++) {
		if (i<0 || i>=realMap->getX()) {
			continue;
		}
		for (int j = currentLocation->getyCoord() - visibleRange; j <= currentLocation->getyCoord() + visibleRange; j++) {
			if (j<0 || j>=realMap->getY()) {
				continue;
			}
			//setting the visible map to have the same values as the real map within the visible range
			visibleMap->setPointStatus(i, j, realMap->getPointStatus(i, j));
		}
	}
}

void DynamicRouter::initRouter()
{
	currentLocation = realMap->getStart();
	currentLocation->setStatus(CURRENT);
}

DynamicRouter::DynamicRouter(RoutingMap* map, RoutingMap* visible, int range) : StaticRouter(visibleMap)
{
	visibleRange = range;
	visibleMap = visible;
	realMap = map;
	currentLocation = realMap->getStart();
	
}

int DynamicRouter::optimizePath(HWND window)
{
	initRouter();
	
	while (currentLocation != endPoint) {
		int testValue = StaticRouter::optimizePath();
		if (testValue == 1) {
			return 1;
		}
		//moving the current position three spaces along
		for (int i = 0; i < 3; i++) {
			if (currentLocation->getNext() == nullptr) {
				break;
			}
			currentLocation = currentLocation->getNext();
		}
		updateVisible();
		currentLocation->setStatus(CURRENT);
		RedrawWindow(window, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	}
	return 0;
}
