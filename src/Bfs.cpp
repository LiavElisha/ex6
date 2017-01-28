//
// Created by liav on 22/11/16.
//

#include "Bfs.h"
#include "NodePoint.h"
std::deque<AbstractNode*> Bfs::theShortestWay(AbstractNode* start,
                                              AbstractNode* end){

    // deque for nodes
    std::deque<AbstractNode*> deque1;
    // deque for neighbor of specific node
    std::deque<AbstractNode*> deque2;
    std::deque<AbstractNode*> resetNodes1;
    std::stack<AbstractNode*> resetNodes2;

    // stack for the shortest way
    std::stack<AbstractNode*> stack;
    std::deque<AbstractNode*> finalRoute;
    AbstractNode* node;
    AbstractNode* nodeNeighbor;

    deque1.push_back(start);
    while(!deque1.empty()){
        node = deque1.at(0);
        // find the neighbors of this node
        deque2 = node->getNeighbors();
        while (!deque2.empty()){
            nodeNeighbor = deque2.at(0);
            // a stop condition - if this point is the destination - stop
            if (nodeNeighbor == end) {
                nodeNeighbor->setPapa(node);
                break;
            }
            // if the node wasn't marked, marker him, set is flag and push hin deque 1
            if(!nodeNeighbor->getFlag()&&(!nodeNeighbor->getIsObstacle())){
                nodeNeighbor->setPapa(node);
                nodeNeighbor->setFlag();
                deque1.push_back(nodeNeighbor);
            }
            resetNodes1.push_back(deque2.front());
            deque2.pop_front();
        }
        resetNodes1.push_back(deque1.front());
        deque1.pop_front();
        if (nodeNeighbor == end){
            node = nodeNeighbor;
            break;
        }
    }

    // if the last point is not the destination return empty deque
    if (node != end){
        return finalRoute;
    }



    // add to the stack the Nodes in order
    while (true){
        stack.push(node);
        if(node == start){
            break;
        }
        node = node->getPapa();
    }
    while (!stack.empty()){
        node= stack.top();
        stack.pop();
        node->setNotFlag();
        node->setPapa(0);
        resetNodes2.push(node);
    }
    while(!resetNodes2.empty()){
        stack.push(resetNodes2.top());
        resetNodes2.pop();
    }

    while(!resetNodes1.empty()){
        resetNodes1.front()->setNotFlag();
        resetNodes1.pop_front();
    }
    while(!(stack.empty())){
        finalRoute.push_back(stack.top());
        stack.pop();

    }

    return finalRoute;
}



Bfs::~Bfs() {};