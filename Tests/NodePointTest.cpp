//
// Created by yoav on 03/12/16.
//

#include "NodePointTest.h"
#include "gtest/gtest.h"
#include "../src/NodePoint.h"

TEST(NodePointTest, getAndSetFather){
    NodePoint* father = new NodePoint (1,1);
    NodePoint* son =  new NodePoint(0,0);
    son->setPapa(father);
    EXPECT_EQ(son->getPapa()!=0, true)
                        <<"the getPapa function doesn't work properly the father is null ";
    NodePoint* replaceFather = new NodePoint(2,2);
    delete (son->getPapa());
    son->setPapa(replaceFather);
    EXPECT_EQ(son->getPapa()->getPapa() !=0, false)
                        << "the father of the father should be null and the constructor"
                        "doesn't work as it should.";
    delete(son);
    delete (replaceFather);
}

TEST(NodePointTest, getAndSetPoint){
    NodePoint* son =  new NodePoint(0,0);
    son->setPoint(1,1);

    EXPECT_EQ(son->getPoint().getX()==1, true)
                        <<"the setPoint function doesn't work properly";
    delete(son);
}

TEST(NodePointTest, getAndSetFLAG){
    NodePoint* son =  new NodePoint(0,0);
    son->setFlag();
    EXPECT_EQ(son->getFlag()==1, true)
                        <<"the setFlag function doesn't work properly";
    delete(son);
}

TEST(NodePointTest, addNeighborAndGetNeighbors){
    NodePoint* son =  new NodePoint(0,0);
    NodePoint* neighbor =  new NodePoint(1,1);
    son->addNeighbor(neighbor);
    EXPECT_EQ(son->getNeighbors().size()!=0, true)
                        <<"there should be another neighbor and there isn't one"
                        "there is a problem with the addNeighbor method";
    delete(son->getNeighbors().front());
    delete(son);
}

TEST(NodePointTest, isEqualOperatorTest){
    NodePoint nodePoint1 = NodePoint(0,0);
    NodePoint nodePoint2 = NodePoint(1,1);
    NodePoint nodePoint3 = NodePoint(0,0);
    EXPECT_NE(nodePoint1==nodePoint2, true) <<"the points are equal";
    EXPECT_EQ(nodePoint1==nodePoint3, true) <<"the points aren't equal";
}

TEST(NodePointTest, setAndGetIsObstacle){
    NodePoint nodePoint1 = NodePoint(0,0);
    nodePoint1.setIsObstacle();
    EXPECT_EQ(nodePoint1.getIsObstacle()==1,true)<<"the node point should be an obstacle";
}

