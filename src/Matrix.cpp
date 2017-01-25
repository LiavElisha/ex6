//
// Created by liav on 21/11/16.
//

#include "Matrix.h"

Matrix::Matrix(int xSize, int ySize){
    x = xSize;
    y = ySize;

    // create NodePoint objects
    for(int i = 0; i<x; i++)
        for(int j=0; j<y; j++){
            nodes[i][j] = new NodePoint(i,j);
    }

    // add the neighbors of every NodePoint
    for(int i = 0; i<x; i++)
        for(int j=0; j<y; j++){

            if (i-1 >= 0){
                nodes[i][j]->addNeighbor(nodes[i-1][j]);
            }
            if(j+1 < y){
                nodes[i][j]->addNeighbor(nodes[i][j+1]);
            }
            if(i+1 < x){
                nodes[i][j]->addNeighbor(nodes[i+1][j]);
            }
            if(j-1 >= 0){
                nodes[i][j]->addNeighbor(nodes[i][j-1]);
            }
        }
}

Matrix::~Matrix() {
    for (int i = 0; i < x; i++)
        for (int j = 0; j < y; j++) {
            delete nodes[i][j];
        }
}


AbstractNode* Matrix::getNode(AbstractNode* node){
    NodePoint* nodePoint = (NodePoint*) node;
    for(int i = 0; i<x; i++)
        for(int j=0; j<y; j++){
            if (nodePoint->getPoint() == nodes[i][j]->getPoint()){
                return nodes[i][j];
            }
        }
}