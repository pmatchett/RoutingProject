#pragma once
#include <vector>
#include "RoutingMap.h"

//This header file was originally designed by me and a group mate (Patrick and Matt Kadatdz) for the capstone project SAFE 
//and I am reusing most of the code with slight changes
class StaticRouter
{
protected:
    //graph that will be used to generate optimal path
    RoutingMap* map;
    //list that stores all nodes currently available for path detection
    std::vector<Node*> openList;
    //list of nodes that have been visited with the best path determined, the value is true if they have been visited, false otherwise
    std::vector<bool> closedList;
    //The point on the graph where the routing algorithm will begin
    Node* startPoint;
    //The point on the graph where the routing algorithm is attempting to reach
    Node* endPoint;
    //helper function to determine if the end point has been reached
    //currentLocation = node to be checked if it the end node
    //return true if the node is the end node
    bool isEnd(Node* currentLocation);
    //helper function to calculate the distance heuristic of Nodes (distance to the end node)
    //current = node for which the distance will be calculated
    //returns the distance heuristic calculated
    double calculateDistance(Node* current);
    //helper function to check if Node is currently on the open list
    //current = node that will be checked for the open list
    //returns true if the node is on the open list
    bool onOpen(Node* current);
    //Set the included flag on all nodes included in the path
    void tracePath();
    //function that resets the routeplanner for a new route
    void reset();
    //helper function to compare if two doubles are equal (to make up for potential innacuracies in double storage)
    bool doubleCompare(double first, double second);
    //helper function to set the start and end points to those of the map
    void setMapStartEnd();
    //sets the start point to the given Node
    void setStart(Node* start);
    //sets the end point to the given Node
    void setEnd(Node* end);

public:
    //constructor that assigns a graph to be used
    StaticRouter(RoutingMap* map);

    //generates the optimal path to get from the start point to the end point using the A* algorithm
    //returns a 0 if a path was found from start to end, 1 if there was no viable path, 2 if an error
    int optimizePath();

};

