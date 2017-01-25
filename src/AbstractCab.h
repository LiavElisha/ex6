//
// Created by yoav on 02/12/16.
//

#ifndef EX11_ABSTRACTCAB_H
#define EX11_ABSTRACTCAB_H

#include <string>
#include <stack>
#include "NodePoint.h"
#include "Bfs.h"
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


/*
 * clas name: AbstractCab.
 * the class is and abstract class which 2 other classes implements its method.
 */

class AbstractCab {



protected:
    //members
    deque <AbstractNode*>* shortestPath;
    Bfs* navigator;
    int cabId;
    int type;
    int meters;
    char manufacturer;
    char color;
    float coefficient;
    int speed;
    AbstractNode* location;
    virtual void setSpeed(int speed1) =0;

public:

public:

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & cabId;
        ar & type;
        ar & meters;
        ar & manufacturer;
        ar & color;
        ar & coefficient;
        ar & speed;
    }


    //getters and setters.
    virtual int getType()=0;
    virtual AbstractNode*& getLocation()=0;
    virtual int getCabId()=0;
    virtual int getMeterPassed()=0;
    virtual void setShortestPath(deque<AbstractNode*>& path)=0;
    virtual deque<AbstractNode*> getShortestPath()=0; //for debugging.
    virtual Bfs*& getNavigator()=0;

    virtual int moveOneStep() =0;//returns the amount of steps did and moves the cab.
    virtual void addMetersPassed(int meters)=0;// add meters to the meters member.
    virtual void setLocation(AbstractNode*& location1)=0;// add meters to the meters member.
    virtual ~AbstractCab()=0;//destructor.


};
BOOST_SERIALIZATION_ASSUME_ABSTRACT(AbstractCab);

#endif //EX11_ABSTRACTCAB_H
