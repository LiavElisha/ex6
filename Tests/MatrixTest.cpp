//
// Created by liav on 02/12/16.
//

#include "MatrixTest.h"
#include "../src/Matrix.h"

TEST(MatrixTests, getNode){

    Matrix matrix(10, 10);


    vector<NodePoint> nodes(3);
    vector<AbstractNode*> abstractNodes(3);

    nodes[0] = NodePoint(3,3);
    nodes[1] = NodePoint(7,6);
    nodes[2] = NodePoint(9,0);

    abstractNodes[0] = matrix.getNode(&nodes[0]);
    abstractNodes[1] = matrix.getNode(&nodes[1]);
    abstractNodes[2] = matrix.getNode(&nodes[2]);

    for (unsigned i = 0; i < abstractNodes.size(); ++i) {
        EXPECT_EQ(((NodePoint*)abstractNodes[i])->getPoint(),
                  nodes[i].getPoint()) <<"the value of x is wrong in point " <<i;
    }

}