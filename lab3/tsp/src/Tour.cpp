#include <iostream>
#include "Tour.h"
#include "Node.h"
#include "Point.h"

Tour::Tour()
{
    startNode = nullptr;
}

Tour::Tour(Point a, Point b, Point c, Point d)
{
       startNode = new Node(a);
       startNode->next = new Node(b, new Node(c, new Node(d, startNode)));
}

Tour::~Tour()
{
    if (startNode == nullptr){
        return;
    }
    Node* currentNode = startNode;
    Node* nextNode;
    while (currentNode->next != startNode){
        nextNode = currentNode->next;
        delete currentNode;
        currentNode = nextNode;
    }
    delete currentNode;
    return;
}

void Tour::show()
{
    if (startNode == nullptr){
        cout << "null" << endl;
        return;
    }
    Node* currentNode = startNode;
    while (currentNode->next != startNode){
        cout << currentNode->point << endl;
        currentNode = currentNode->next;
    }
    cout << currentNode->point << endl;
    return;
}

void Tour::draw(QGraphicsScene *scene)
{
    if (startNode == nullptr){
        return;
    }
    Node* currentNode = startNode;
    while (currentNode->next != startNode){
        currentNode->point.drawTo(currentNode->next->point, scene);
        currentNode = currentNode->next;
    }
    currentNode->point.drawTo(currentNode->next->point, scene);
    return;
}

int Tour::size()
{
    int counter = 0;
    if (startNode == nullptr){
        return counter;
    }
    Node* currentNode = startNode;

    while (currentNode->next != startNode){
        counter++;
        currentNode = currentNode->next;
    }
    counter++;
    return counter;
}

double Tour::distance()
{
    double dist = 0;
    if (startNode == nullptr){
        return dist;
    }
    Node* currentNode = startNode;
    while (currentNode->next != startNode){
        dist += currentNode->point.distanceTo(currentNode->next->point);
        currentNode = currentNode->next;
    }
    dist += currentNode->point.distanceTo(currentNode->next->point);
    return dist;
}

void Tour::insertNearest(Point p)
{
    Node* nearestNode;

    if (startNode == nullptr){
        startNode = new Node(p);
        startNode->next = startNode;
        return;
    }
    double currentDistance;
    Node* currentNode = startNode;
    double nearestDistance = numeric_limits<double>::max();

    do{
        currentDistance = p.distanceTo(currentNode->point);
        if(currentDistance < nearestDistance){
            nearestDistance = currentDistance;
            nearestNode = currentNode;
        }
        currentNode = currentNode->next;
    }while(currentNode != startNode);

    Node* newNode = new Node(p, nearestNode->next);
    nearestNode->next = newNode;
    return;
}

void Tour::insertSmallest(Point p)
{
    Node* smallestNode;

    if (startNode == nullptr){
        startNode = new Node(p);
        startNode->next = startNode;
        return;
    }
    double currentDistance;
    Node* currentNode = startNode;
    double smallestDistance = numeric_limits<double>::max();

    do{
        currentDistance = p.distanceTo(currentNode->point) +
                p.distanceTo(currentNode->next->point) -
                currentNode->point.distanceTo(currentNode->next->point);

        if(currentDistance < smallestDistance){
            smallestDistance = currentDistance;
            smallestNode = currentNode;
        }
        currentNode = currentNode->next;
    }while(currentNode != startNode);

    Node* newNode = new Node(p, smallestNode->next);
    smallestNode->next = newNode;
    return;
}
