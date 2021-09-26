#ifndef SUPERPIXEL_H
#define SUPERPIXEL_H

#include "BinarySearchTree.h"

class SuperPixel {

    BST<int,int> Tags;
    int MaxTag;
    int MaxScore;

public:
    SuperPixel();
    void InsertTag(int tag,int score);
    void DeleteTag(int tag);
    int GetMaxScore(int* score) const;
    void ResetIterator();
    int NextIteration(int* score);
    int GetNumOfTags();
    void MergeSuperPixel(SuperPixel* SP);
};


#endif //SUPERPIXEL_H
