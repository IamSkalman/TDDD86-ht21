#ifndef TOUR_H
#define TOUR_H

#include "Node.h"
#include "Point.h"

class Tour {
public:

    // Initializes the startNode pointer as nullptr
    Tour();

    // Sets the startNode to 4 Nodes for each Point
    // Each node has a pointer to the next node such as:
    // a -> b -> c -> d -> a (circular)
    Tour(Point a, Point b, Point c, Point d);

    // Iterates through each node, saves the pointer to next and then deletes the node
    // After the while loop one node is left and it is deleted aswell
    // (currentNode and nextNode points at the same Node in the end)
    ~Tour();

    // Prints out, beginning with the startNode, the Point for every node
    void show();

    // Iterates through each node and draws a line from the current node to the next node
    void draw(QGraphicsScene* scene);

    // Iterates through each node counting each iteration and returns the amount of existing nodes
    int size();

    // Iterates through each node adding the distance between each node and then returns the
    // total distance for the whole tour
    double distance();

    // Iterates through each previously created node and checks the distance from the Point p to the node.
    // If the distance is the smallest, the distance is saved for comparing in next iterations
    // and the therefore nearestNode is also saved. After each node has been checked a newNode is
    // created for Point p and it points at the nearestNode's next. The nearestNode's next is replaced
    // with a pointer to the newNode (nearestNode -> newNode -> nearestNode's previous next)
    void insertNearest(Point p);

    // Iterates through each previously created node and checks
    // (distance from the Point p to the node) + (distance from the Point p to the node's next) -
    // (distance from the node to the node's next) = difference in distance
    // If the difference is the smallest, the difference is saved for comparing in next iterations
    // and the therefore smallestNode is also saved. After each node has been checked a newNode is
    // created for Point p and it points at the smallestNode's next. The smallestNode's next is replaced
    // with a pointer to the newNode (smallestNode -> newNode -> smallestNode's previous next)
    void insertSmallest(Point p);


private:
    Node* startNode;
};

#endif // TOUR_H
