//
// Created by liav on 21/11/16.
//

#ifndef EX11_GRID_H
#define EX11_GRID_H


#include "AbstractNode.h"
/* class name : Grid
 * Abstract class that have one virtual function, it allow to use
 * Bfs algorithm with every "sons" class of Grid
 */
class Grid {
    /* virtual function that return the address of Node which
    * has same value like the Abstracnode input
     */
public:
    virtual AbstractNode* getNode(AbstractNode* node) = 0;
    virtual ~Grid()=0;

};


#endif //EX11_GRID_H
