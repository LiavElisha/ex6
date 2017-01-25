//
// Created by liav on 21/11/16.
//

#include "Point.h"

Point::Point(int x1, int y1) {
    x = x1;
    y = y1;
}
Point::Point() {};
int Point::getX()const {
    return x;
}

int Point::getY()const {
    return y;
}

Point::Point(const Point &obj){
    x = obj.getX();
    y = obj.getY();
}

bool Point::operator ==(const Point &p) const {
    return ((x == p.getX()) && (y == p.getY()));
}


std::ostream &operator<<( std::ostream &output, const Point &r){
    output << "(" << r.getX() << "," << r.getY() << ")\n";
    return output;
}

