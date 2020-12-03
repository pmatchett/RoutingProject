#include "DynamicRouter.h"
#include "framework.h" // this is only used until I can get multiple threads to track movement

void DynamicRouter::updateVisible()
{
	//the following line is only there until a function is created to init the router once the map has been chosen
	currentLocation = realMap->getStart();

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

DynamicRouter::DynamicRouter(RoutingMap* map, RoutingMap* visible, int range) : StaticRouter(visibleMap)
{
	visibleRange = range;
	visibleMap = visible;
	realMap = map;
	currentLocation = realMap->getStart();
	
}

int DynamicRouter::optimizePath(HWND window)
{
	RedrawWindow(window, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
	return 0;
}
