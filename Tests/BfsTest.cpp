//
// Created by liav on 02/12/16.
//

#include "BfsTest.h"
#include "../src/Point.h"
#include "../src/AbstractNode.h"
#include "../src/NodePoint.h"
#include "../src/Matrix.h"
#include "../src/Bfs.h"


TEST(BfsTests, BfsAlgorithm){

    int counter = 0;
    Matrix matrix(10, 10);
    NodePoint node1(0,0), node2(3, 5);
    AbstractNode* start = matrix.getNode(&node1);
    AbstractNode* end = matrix.getNode(&node2);
    Bfs bfs;
    stack<Point> pointsStack;
    for (unsigned i = 5, j = 3; j > 0; --j) {
        pointsStack.push(Point(j,i));
    }
    for (int i = 5; i >= 0; --i) {
        pointsStack.push(Point(0, i));
    }
    deque<AbstractNode*> deque1 = bfs.theShortestWay(start, end);
    ASSERT_EQ(deque1.size(), pointsStack.size())<<"stack and ponitsStack have different size";

    while (!deque1.empty() && !pointsStack.empty()) {

        NodePoint* node =(NodePoint*) deque1.front();
        EXPECT_EQ(node->getPoint(), pointsStack.top()) <<"the bfs algorithm is wrong at point "
                                                       << counter;
        pointsStack.pop();
        deque1.pop_front();
        counter++;
    }
}
