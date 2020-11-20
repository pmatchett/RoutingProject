#pragma once
//This header file was originally designed by me and a group mate (Patrick and Matt Kadatdz) for the capstone project SAFE 
//and I am reusing most of the code with slight changes
#include <windows.h>
//the followings definitions are for the status of the node
#define FREE 0 
#define OBSTACLE 1 
#define START 2 
#define END 3 
class Node {
private:

    //A static counter for the nodes
    static int counter;
    //the coordinates of the node
    POINT coordinates;
    //the previous node in the generated path
    Node* prevNode;
    //the hueristic value for the distance from the node to the end point of the route
    double distanceWeight;
    //The sum of all heuristics, currently this is only the distance weight, but more could be added to further customize
    double totalHeuristic;
    //each int represents a state: 0 = free, 1 = obstacle, 2 = start, 3 = end
    int status;
    //the id of the node, generated from the static counter
    int id;
    //contains the distance already traveled to reach the current node
    double distanceTravelled;



public:
    //Node constructor, type is what styele of node is being created, weights are 0
    Node(int x, int y, int type);

    ~Node();

    //resets the id counter
    static void resetCounter();

    //sets the status of the point to a new value
    void setStatus(int newStatus);

    //sets the previous node in the chain
    void setPrev(Node* prev);

    //Returns the node's x coordinate
    double getxCoord();

    //Returns the node's y coordinate
    double getyCoord();

    //Currently I am not using any setters for coords as they should not be changed once created

    //returns the node's id
    int getId();

    //returns the integer value that represents the status of the coordinate
    int getStatus();

    //retuns the previous node in the path
    Node* getPrev();

    //sets the values of the distance heuristic
    void setDistanceWeight(double value);

    //returns the sum of all heuristics
    double getHeuristic();

    //returns the current distance travelled to get to this Node
    double getDistanceTravelled();

    //sets the total distance traveled to ge to this node
    void setDistanceTravelled(double num);

    double euclideanDistance(Node* other);

    //Overloading the - operator, returns the euclidean distance between two nodes
    double operator- (Node* rhs);

};
