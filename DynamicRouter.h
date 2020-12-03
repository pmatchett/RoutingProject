#pragma once
#include "StaticRouter.h"
class DynamicRouter : protected StaticRouter
{
private:
	RoutingMap* visibleMap;
	RoutingMap* realMap;
	//the radius range that the router can see from it's current position
	int visibleRange;
	Node* currentLocation;

	//update the visible map to track the current position
	//void updateVisible();

public:
	DynamicRouter(RoutingMap* map, RoutingMap* visible, int range);
	void updateVisible();

	//The HWND is only being passed so that I can redraw the window until multiple threads work
	int optimizePath(HWND window);
};

