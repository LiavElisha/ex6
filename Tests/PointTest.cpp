//

// Created by liav on 01/12/16.
//

#include "PointTest.h"
#include "../src/Point.h"

TEST(PointTests, getX){

    Point p0(0,0), p1(1,1), p2(2,2), p3(3,3), p4(4,4), p5(5,5);

    vector<int> xPoints(6), x(6);
    xPoints[0] = p0.getX();
    xPoints[1] = p1.getX();
    xPoints[2] = p2.getX();
    xPoints[3] = p3.getX();
    xPoints[4] = p4.getX();
    xPoints[5] = p5.getX();

    for (unsigned i = 0; i < x.size(); ++i) {
        x[i] = i;
    }

    for (unsigned i = 0; i < x.size(); ++i) {
        EXPECT_EQ(xPoints[i], x[i]) <<"the value of x is wrong in point " <<i;
    }
}


TEST(PointTests, getY){

    Point p0(0,0), p1(1,1), p2(2,2), p3(3,3), p4(4,4), p5(5,5);

    vector<int> yPoints(6), y(6);
    yPoints[0] = p0.getX();
    yPoints[1] = p1.getX();
    yPoints[2] = p2.getX();
    yPoints[3] = p3.getX();
    yPoints[4] = p4.getX();
    yPoints[5] = p5.getX();

    for (unsigned i = 0; i < y.size(); ++i) {
        y[i] = i;
    }

    for (unsigned i = 0; i < y.size(); ++i) {
        EXPECT_EQ(yPoints[i], y[i]) <<"the value of y is wrong in point " <<i;
    }
}




TEST(PointTests, boolOperator) {

    Point p0(0, 0), p1(1, 1), p2(2, 2), p3(3, 3);
    Point p6(0, 0), p7(1, 1), p10(4, 4), p11(5, 5);

    vector<Point> points1(4), points2(4);
    points1[0] = p0;
    points1[1] = p1;
    points1[2] = p2;
    points1[3] = p3;

    points2[0] = p6;
    points2[1] = p7;
    points2[2] = p10;
    points2[3] = p11;

    for (unsigned i = 0; i < 2; ++i)
        EXPECT_EQ(points1[i], points2[i]) << "the points differ at index " << i;


    for (unsigned i = 2; i < points1.size(); ++i)
        EXPECT_EQ(points1[i] == points2[i], false) << "the points same at index " << i;
}


TEST(PointTests, outptOperator) {

    Point p0(0, 0), p1(-1, -1);


    ostringstream out;
    out <<p0;
    EXPECT_EQ(out.str(), "(0,0)\n") << "wrong print to point " ;

    ostringstream out2;
    out2 <<p1;
    EXPECT_EQ(out2.str(), "(-1,-1)\n") << "wrong print to point " ;

}
