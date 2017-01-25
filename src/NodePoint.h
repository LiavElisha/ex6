//
// Created by liav on 21/11/16.
//

#ifndef EX11_NODEPOINT_H
#define EX11_NODEPOINT_H


#include <iostream>
#include "AbstractNode.h"
#include "Point.h"
#include <iostream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <boost/archive/text_oarchive.hpp>
#include <boost/archive/text_iarchive.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string/predicate.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/assign/list_of.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/iostreams/device/back_inserter.hpp>
#include <boost/iostreams/stream.hpp>
#include <boost/archive/binary_oarchive.hpp>
#include <boost/archive/binary_iarchive.hpp>
#include <boost/serialization/deque.hpp>
using namespace std;
using namespace boost::archive;

/* class name : NodePoint
 * class which inherit from AbstractNode, by this class we can
 * create a map that every object from this class is a square on the map
 */
class NodePoint:public AbstractNode{
private:
    bool flag;
    AbstractNode* papa;
    Point p;
    std::deque<AbstractNode*> neighbors;
    int isObstacle;
protected:
    std::ostream& print(std::ostream &output) const;
public:

    // constructors
    NodePoint(Point point, NodePoint* father);
    NodePoint(int x, int y, NodePoint* father);
    NodePoint(Point point);
    NodePoint(int x, int y);
    NodePoint();

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar&boost::serialization::base_object<AbstractNode>(*this);
        ar & flag;
       // AbstractNode* papa;
        ar & p;
       // ar & neighbors;
        ar & isObstacle;
    }



    // "==" definition
    bool operator==(const NodePoint &r) const;

    // "!=" definition
    bool operator!=(const NodePoint &r) const;


    // get and set functions
    void setPapa(AbstractNode* node);
    AbstractNode* getPapa();
    void setPoint(int x, int y);
    Point getPoint()const;
    void setFlag();
    void setNotFlag();
    int getFlag();
    void setIsObstacle();
    int getIsObstacle();
    std::deque<AbstractNode*> getNeighbors();

    // copy function
    NodePoint(const NodePoint &obj);
    // add to the deque Node which near to this NodePoint
    void addNeighbor(AbstractNode* node);
    Point getPoint();
    ~NodePoint();
};


#endif //EX11_NODEPOINT_H
