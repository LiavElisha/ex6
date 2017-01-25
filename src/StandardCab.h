//
// Created by yoav on 02/12/16.
//

#ifndef EX11_STANDARDCAB_H
#define EX11_STANDARDCAB_H


#include "AbstractCab.h"
#include <string>
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


/*
 * class name: StandardCab that inherits from AbstractCab.
 */
class StandardCab: public AbstractCab {
public:
    //constructor.
    StandardCab(int cabId1 ,int kilometers1,char manufacturer1, char color1, AbstractNode*& l);
    StandardCab();

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar&boost::serialization::base_object<AbstractCab>(*this);
    }

    // getters and setters.
    void setSpeed(int speed1);
    int getSpeed();
    float getTariff();
    int getType();
    AbstractNode*& getLocation();
    int moveOneStep();//the method that moves the cab.
    int getCabId();
    Bfs*& getNavigator();
    void setShortestPath(deque<AbstractNode*>& path);
    deque<AbstractNode*> getShortestPath(); //for debugging.
    void addMetersPassed(int meters);
    int getMeterPassed();
    void setLocation(AbstractNode*& location1);
    ~StandardCab();

};


#endif //EX11_STANDARDCAB_H

