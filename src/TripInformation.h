//
// Created by liav on 01/12/16.
//

#ifndef EX11_TRIPINOFRMATION_H
#define EX11_TRIPINOFRMATION_H

#include <iostream>
#include "NodePoint.h"
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


class TripInformation {
private:
    int rideId;
    int meterPassed;
    AbstractNode* source;
    AbstractNode* destination;
    int numberOfPassangers;
    double tariff;
    int timeOfStart;
    deque <AbstractNode*>* shortestPath;
    bool computeShortestWayDone;

public:
    // constructor
    TripInformation();
    TripInformation (int rideId2, int meterPassed2, AbstractNode* source2,
                     AbstractNode* destination2 ,double tariff2, int pass);
    TripInformation (int rideId2, int xStart, int yStart, int xEnd, int yEnd,
                      int pass,double tariff2, int timeOfStart1);

    friend class boost::serialization::access;
    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & rideId;
        ar & meterPassed;
        ar & source;
        ar & destination;
        ar & numberOfPassangers;
        ar & tariff;
        ar & timeOfStart;
        ar &shortestPath;
    }



    // get and set functions
    int getRideId();

    void setMetersPassed(int meters);
    int getMetersPassed();
    AbstractNode*& getSource();
    AbstractNode*& getDestination();
    void setTariff(double tariff);
    double getTariff();
    AbstractNode*&  getNextPointOnRounte();
    //AbstractNode*  getNextPointOnRounte();
    void setShortestPath(deque<AbstractNode*>*& path);
    unsigned long getRouteLength();
    int getStartTime();
    void setStartTime(int s);
    void setComputeShortestWayDone();
    bool getComputeShortestWayDone();
    ~TripInformation();


};


#endif //EX11_TRIPINOFRMATION_H
