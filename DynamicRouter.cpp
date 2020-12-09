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
	currentLocation = visibleMap->getStart();
	currentLocation->setStatus(CURRENT);
	updateVisible();
	StaticRouter::setMapStartEnd();
}

DynamicRouter::DynamicRouter(RoutingMap* map, RoutingMap* visible, int range) : StaticRouter(visible)
{
	visibleRange = range;
	visibleMap = visible;
	realMap = map;
	currentLocation = visibleMap->getStart();
	
}

int DynamicRouter::optimizePath(HWND window)
{
	initRouter();
	
	while (currentLocation != endPoint) {
		StaticRouter::setStart(currentLocation);
		//setting the current location to not have a previous so that trace path does not loop forever
		currentLocation->setPrev(nullptr);
		int testValue = StaticRouter::optimizePath();
		if (testValue == 1) {
			return 1;
		}
		//moving the current position three spaces along
		//TODO: set it so that only the current location will have the status and the others will return to normal
		//	Also need to remove the previous planned routes, but not where it actually visited
		//currentLocation->setStatus(FREE);
		for (int i = 0; i < 3; i++) {
			if (currentLocation->getNext() == nullptr) {
				break;
			}
			OutputDebugString(_T("Advancing current location\n"));
			currentLocation = currentLocation->getNext();
		}
		updateVisible();
		currentLocation->setStatus(CURRENT);
		RedrawWindow(window, NULL, NULL, RDW_INVALIDATE | RDW_UPDATENOW);
		Sleep(1000);
	}
	return 0;
}
