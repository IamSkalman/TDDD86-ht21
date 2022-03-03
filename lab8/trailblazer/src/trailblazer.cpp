#include "costs.h"
#include "trailblazer.h"
#include "algorithm"
#include "math.h"
#include "pqueue.h"
#include "queue"

using namespace std;

void DFSTraversal(vector<Vertex*>& path, Vertex* start, Vertex* end, BasicGraph& graph){
    start->visited = true;
    if(start == end){
        start->setColor(GREEN);
        return;
    }
    Vertex* nextNode = nullptr;
    for(Vertex* node: graph.getNeighbors(start)){
        if(!node->visited){
            nextNode = node;
            start->setColor(GREEN);
            path.push_back(nextNode);
            nextNode->previous = start;
            DFSTraversal(path, nextNode, end, graph);
            return;
        }
    }
    if(nextNode == nullptr){
        start->setColor(GRAY);
        path.pop_back();
        if(!(start->previous == NULL)){
            DFSTraversal(path, start->previous, end, graph);
        }

    }

}

vector<Node *> depthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    path.push_back(start);
    DFSTraversal(path, start, end, graph);
    return path;
}

vector<Node *> breadthFirstSearch(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    queue<Vertex*> vertexQueue;
    Vertex* currentVertex;

    vertexQueue.push(start);
    start->visited = true;

    while(!vertexQueue.empty()){
        currentVertex = vertexQueue.front();
        vertexQueue.pop();
        currentVertex->setColor(GREEN);
        if(currentVertex == end){
            path.push_back(currentVertex);
            while(currentVertex->previous != NULL){
                path.push_back(currentVertex->previous);
                currentVertex = currentVertex->previous;
            }
            //reverse(path.begin(), path.end());
            return path;
        }
        for(Vertex* neighbour: graph.getNeighbors(currentVertex)){
            if(!neighbour->visited){
                neighbour->visited = true;
                neighbour->previous = currentVertex;
                vertexQueue.push(neighbour);
                neighbour->setColor(YELLOW);
            }
        }
    }

    return path;
}

vector<Node *> dijkstrasAlgorithm(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> vertexQueue;

    Vertex* currentVertex;
    vertexQueue.enqueue(start, start->cost);

    while(!vertexQueue.isEmpty()){
        currentVertex = vertexQueue.dequeue();
        currentVertex->visited = true;
        currentVertex->setColor(GREEN);
        if(currentVertex == end){
            path.push_back(currentVertex);
            while(currentVertex->previous != NULL){
                path.push_back(currentVertex->previous);
                currentVertex = currentVertex->previous;
            }
            //reverse(path.begin(), path.end());
            return path;
        }
        for(Arc* edge: currentVertex->arcs){
            Vertex* neighbour = edge->finish;
            if(!neighbour->visited){
                if(neighbour->cost == 0){
                    neighbour->cost = currentVertex->cost + edge->cost;
                    neighbour->previous = currentVertex;
                    vertexQueue.enqueue(neighbour, neighbour->cost);
                    neighbour->setColor(YELLOW);
                }
                else if(neighbour->cost > currentVertex->cost + edge->cost){    //Om en billigare väg till neighbour hittas, uppdateras cost (Priority)
                    neighbour->cost = currentVertex->cost + edge->cost;
                    neighbour->previous = currentVertex;
                    vertexQueue.changePriority(neighbour, neighbour->cost);
                }

            }
        }
    }




    return path;
}

vector<Node *> aStar(BasicGraph& graph, Vertex* start, Vertex* end) {
    graph.resetData();
    vector<Vertex*> path;
    PriorityQueue<Vertex*> vertexQueue;
    Vertex* currentVertex;

    vertexQueue.enqueue(start, start->cost);

    while(!vertexQueue.isEmpty()){
        currentVertex = vertexQueue.dequeue();
        currentVertex->visited = true;
        currentVertex->setColor(GREEN);
        if(currentVertex == end){
            path.push_back(currentVertex);
            while(currentVertex->previous != NULL){
                path.push_back(currentVertex->previous);
                currentVertex = currentVertex->previous;
            }
            //reverse(path.begin(), path.end());
            return path;
        }
        for(Arc* edge: currentVertex->arcs){
            Vertex* neighbour = edge->finish;
            if(!neighbour->visited){
                if(neighbour->cost == 0){
                    neighbour->cost = currentVertex->cost + edge->cost;
                    neighbour->previous = currentVertex;
                    vertexQueue.enqueue(neighbour, neighbour->cost + neighbour->heuristic(end));    //Köas med en potentiell cost från neighbour till end
                    neighbour->setColor(YELLOW);
                }
                else if(neighbour->cost > currentVertex->cost + edge->cost){    //Om en billigare väg till neighbour hittas, uppdateras cost (Priority)
                    neighbour->cost = currentVertex->cost + edge->cost;
                    neighbour->previous = currentVertex;
                    vertexQueue.changePriority(neighbour, neighbour->cost + neighbour->heuristic(end));
                }

            }
        }
    }

    return path;
}
