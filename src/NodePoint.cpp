//
// Created by liav on 21/11/16.
//

#include "NodePoint.h"
#include <boost/serialization/export.hpp>

using namespace std;
using namespace boost::archive;


// constructors
NodePoint::NodePoint(Point point, NodePoint* father){
    p = point;
    papa = father;
    flag = false;
    isObstacle=0;
}
NodePoint::NodePoint(int x, int y, NodePoint* father){
    papa = father;
    Point point(x, y);
    p = point;
    flag = false;
    isObstacle=0;
}
NodePoint::NodePoint(int x, int y){
    Point point(x, y);
    p = point;
    papa = 0;
    flag = false;
    isObstacle=0;
}

NodePoint::NodePoint(Point point) {
    p = point;
    papa = 0;
    flag = false;
    isObstacle=0;
}
NodePoint::NodePoint() {
    papa = 0;
    flag = false;
    isObstacle=0;
    p = Point(0,0);

};


// "<<" definition
std::ostream& NodePoint::print(std::ostream &output) const{
    output << p;
    return output;
}

// "==" definition
bool NodePoint::operator ==(const NodePoint &r) const {
    return ((p.getX() == r.getPoint().getX()) && (p.getY() == r.getPoint().getY()));
}

//operator overloading on "!="
bool NodePoint::operator !=(const NodePoint &r) const {//make new test for this method.
    return ((p.getX() != r.getPoint().getX()) || (p.getY() != r.getPoint().getY()));
}


// get/set function
void NodePoint::setPapa(AbstractNode* node){
    papa = node;
}
AbstractNode* NodePoint::getPapa(){
    return papa;
}


void NodePoint::setPoint(int x, int y) {
    p = Point(x,y);
}
Point NodePoint::getPoint()const {
    Point point = p;
    return point;
};


void NodePoint::setFlag(){
    flag = 1;
}

void NodePoint::setNotFlag() {
    flag = 0;
}

int NodePoint::getFlag(){
    return flag;
}

void NodePoint::setIsObstacle(){
    isObstacle=1;
}
int NodePoint::getIsObstacle(){
    return isObstacle;
}

std::deque<AbstractNode*> NodePoint::getNeighbors(){
    return neighbors;
};

// copy function
NodePoint:: NodePoint(const NodePoint &obj){
    p = obj.getPoint();
    flag = obj.flag;
    papa = obj.papa;
}

void NodePoint::addNeighbor(AbstractNode* node){
    neighbors.push_back(node);
}

Point NodePoint::getPoint(){
    Point p1 = p;
    return p1;
}

NodePoint::~NodePoint() {
}
BOOST_CLASS_EXPORT_GUID(NodePoint,"NodePoint");