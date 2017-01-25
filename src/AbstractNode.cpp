//
// Created by liav on 21/11/16.
//

#include "AbstractNode.h"


std::ostream& operator<<( std::ostream &output, const AbstractNode &r){
    return r.print(output);
}
AbstractNode::~AbstractNode(){};