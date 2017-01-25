//
// Created by liav on 21/11/16.
//

#ifndef EX11_ABSTRACTNODE_H
#define EX11_ABSTRACTNODE_H

#include <iostream>
#include <deque>
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
#include <boost/serialization/assume_abstract.hpp>
using namespace std;
using namespace boost::archive;


/* class name : AbstractNode
 * Abstract class that have some virtual functions, this allow to the Bfs
 * being generic
 */
class AbstractNode {
protected:
  //  int isObstacle =0;// flags if the node is an obstacle or not.
    // a function that get the printing from the "sons" classes
    virtual std::ostream& print(std::ostream &output) const = 0;
public:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
    }

    // set function
    virtual void setPapa(AbstractNode* node) = 0;
    // return if the Node marked
    virtual int getFlag() = 0;
    // mark the Node
    virtual void setFlag() = 0;
    virtual void setNotFlag() = 0;
    // return deque with the neighbor of this Node in order
    virtual std::deque<AbstractNode*> getNeighbors() = 0;
    // return the father of this Node
    virtual AbstractNode* getPapa() = 0;
    virtual Point getPoint() = 0;//added this function to return the point of the abstractnode.
    // function that know to print the values of point in this way (x,y)
    friend std::ostream &operator<<( std::ostream &output, const AbstractNode &r);
    virtual void setIsObstacle() = 0;// set the node as an obastacle.
    virtual int getIsObstacle() = 0;// set the node as not an obstacle.
    virtual ~AbstractNode()=0;

};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(AbstractNode);

#endif //EX11_ABSTRACTNODE_H
