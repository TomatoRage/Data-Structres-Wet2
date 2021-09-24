#ifndef FLIPPEDTREE_H
#define FLIPPEDTREE_H

#include "SuperPixel.h"

struct FlippedTreeNode{

    FlippedTreeNode* father;
    int index;
    int TotalSons;
    SuperPixel* SP;

};

#endif //FLIPPEDTREE_H
