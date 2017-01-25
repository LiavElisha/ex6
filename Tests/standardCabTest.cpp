//
// Created by yoav on 03/12/16.
//

#include "gtest/gtest.h"
#include "../src/StandardCab.h"
#include "../src/Matrix.h"

TEST(StandardCabTest,getAndSetSpeedTest){
    Matrix matrix(10,10);
    NodePoint* p =new NodePoint(0,0);
    AbstractNode* abstractNode = matrix.getNode(p);
    delete p;
    StandardCab s = StandardCab(12345678, 1000,'H', 'B',abstractNode);
    EXPECT_EQ(s.getSpeed(), 1) << "the speed isn't what it was meant to be";

}

TEST(StandardCabTest,getAndSetTariff){//test the get and set tariff.
    Matrix matrix(10,10);
    NodePoint* p =new NodePoint(0,0);
    AbstractNode* abstractNode = matrix.getNode(p);
    delete p;
    StandardCab s = StandardCab(12345678, 1000,'H', 'B',abstractNode);
    EXPECT_EQ(s.getTariff(), 1) << "the Tariff isn't what it was meant to be";
}

TEST(StandardCabTest,setAndGetTypeTest){//check the type of the cab.
    Matrix matrix(10,10);
    NodePoint* p =new NodePoint(0,0);
    AbstractNode* abstractNode = matrix.getNode(p);
    delete p;
    StandardCab s = StandardCab(12345678, 1000,'H', 'B',abstractNode);
    EXPECT_EQ(s.getType(), 1) << "the type isn't what it should be";//check that it is fine.

}

TEST(StandardCabTest,locationTest){//check the type of the cab.
    Matrix matrix(10,10);
    NodePoint* p =new NodePoint(0,0);
    AbstractNode* abstractNode = matrix.getNode(p);
    delete p;
    StandardCab l = StandardCab(1234567, 1000,'H', 'B',abstractNode);
    Bfs bfs;
    NodePoint* start = new NodePoint(0,0);
    NodePoint* end = new NodePoint(1,1);
    deque<AbstractNode*> s = bfs.theShortestWay(matrix.getNode(start),matrix.getNode(end));
    l.setShortestPath(s);
    l.moveOneStep();
    l.moveOneStep();
    l.moveOneStep();
    EXPECT_EQ((*(NodePoint*)l.getLocation()).getPoint().getX()!= 0, true)
                        << "the location of the cab in x"
                        " coordinate shouldn't be 0";
    EXPECT_EQ((*(NodePoint*)l.getLocation()).getPoint().getY()!= 0, true)
                        << "the location of the cab in y"
                        " coordinate shouldn't be 0";
    delete(start);
    delete(end);
}



TEST(StandardCabTest,getCabIdTest){//check the cabId of the cab.
    Matrix matrix(10,10);
    NodePoint* p =new NodePoint(0,0);
    AbstractNode* abstractNode = matrix.getNode(p);
    delete p;
    StandardCab l = StandardCab(1234567, 1000,'H', 'B',abstractNode);
    EXPECT_EQ(l.getCabId(), 1234567) << "the id isn't what it should be";//check that it is fine.
}


TEST(StandardCabTest,setTheShortestPath){//check the cabId of the cab.
    Matrix matrix(10,10);
    NodePoint* p =new NodePoint(0,0);
    AbstractNode* abstractNode = matrix.getNode(p);
    delete p;
    StandardCab l = StandardCab(1234567, 1000,'H', 'B',abstractNode);
    Bfs bfs;
    NodePoint* start = new NodePoint(0,0);
    NodePoint* end = new NodePoint(1,1);
    deque<AbstractNode*> s = bfs.theShortestWay(matrix.getNode(start),matrix.getNode(end));
    l.setShortestPath(s);
    l.moveOneStep();
    l.moveOneStep();
    l.moveOneStep();
    EXPECT_EQ((*(NodePoint*)l.getLocation()).getPoint().getX()!= 0, true)
                        << "there was a problem with the set"
                        "the shortest path method";
    EXPECT_EQ((*(NodePoint*)l.getLocation()).getPoint().getY()!= 0, true)
                        <<"there was a problem with the set"
                        "the shortest path method";
    delete(start);
    delete(end);
}

TEST(StandardCabTest,addMetersTest){//check the cabId of the cab.
  Matrix matrix(10,10);
    NodePoint* p =new NodePoint(0,0);
    AbstractNode* abstractNode = matrix.getNode(p);
    delete p;
    StandardCab l = StandardCab(1234567, 1000,'H', 'B',abstractNode);
    l.addMetersPassed(2);
    EXPECT_EQ(l.getMeterPassed()!=0, true) << "there was a problem with the set"
                        "the shortest path method";

}