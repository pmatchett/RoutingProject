#include "Node.h"
#include <cmath>
#include <iostream>
#include <iomanip>

//This source file was originally designed by me and a group mate (Patrick and Matt Kadatdz) for the capstone project SAFE 
//and I am reusing most of the code with slight changes

int Node::counter = 0;

Node::Node(int x, int y, int type)
{
	coordinates.x = x;
	coordinates.y = y;
	status = type;
	id = Node::counter;
	distanceWeight = -1;
	distanceTravelled = 0;
	totalHeuristic = -1;
	prevNode = nullptr;
	nextNode = nullptr;
	includedPath = false;
	//incrementing the static counter for nodes
	Node::counter++;
}


Node::~Node()
{
}

void Node::setStatus(int newStatus)
{
	status = newStatus;
}

void Node::resetCounter() {
	counter = 0;
}


void Node::setPrev(Node* prev)
{
	prevNode = prev;
}

double Node::getxCoord()
{
	return coordinates.x;
}

double Node::getyCoord()
{
	return coordinates.y;
}

int Node::getStatus() {
	return status;
}

int Node::getId()
{
	return id;
}

Node* Node::getPrev()
{
	return prevNode;
}


void Node::setDistanceWeight(double value)
{
	distanceWeight = value;
	totalHeuristic += distanceWeight;
}

double Node::getHeuristic() {
	return totalHeuristic;
}

double Node::getDistanceTravelled() {
	return distanceTravelled;
}

void Node::setDistanceTravelled(double num) {
	distanceTravelled = num;
}

double Node::euclideanDistance(Node* other)
{
	double xDist = abs(this->coordinates.x - other->coordinates.x);
	double yDist = abs(this->coordinates.y - other->coordinates.y);
	return sqrt(pow(xDist, 2) + pow(yDist, 2));
}

double Node::operator- (Node* rhs) {
	double xDist = abs(this->coordinates.x - rhs->coordinates.x);
	double yDist = abs(this->coordinates.y - rhs->coordinates.y);
	return sqrt(pow(xDist, 2) + pow(yDist, 2));
}

bool Node::getIncluded()
{
	return includedPath;
}

void Node::setIncluded(bool include)
{
	includedPath = include;
}

void Node::setNextNode(Node* next)
{
	nextNode = next;
}

Node* Node::getNext()
{
	return nextNode;
}
