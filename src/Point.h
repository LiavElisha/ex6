//
// Created by liav on 21/11/16.
//

#ifndef EX11_POINT_H
#define EX11_POINT_H
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

using namespace std;
using namespace boost::archive;

/* class name : Point
 * class that have 2 value (x and y) that represented his location
 * on the coordinate
 */
class Point {
private:
    int x;
    int y;
public:
    // constructors
    Point(int x1, int y1);
    Point();
    // copy function
    Point(const Point &obj);

    friend class boost::serialization::access;

    template<class Archive>
    void serialize(Archive &ar, const unsigned int version)
    {
        ar & x;
        ar & y;
    }


    // access to xPoint
    int getX()const;
    // access to yPoint
    int getY()const;

    // define "==" relation between different points
    bool operator==(const Point &p) const;
    // function that know to print the values of point in this way (x,y)
    friend std::ostream &operator<<( std::ostream &output, const Point &r);

};


#endif //EX11_POINT_H
