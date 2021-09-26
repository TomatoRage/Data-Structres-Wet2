#ifndef IMAGE_H
#define IMAGE_H

#include "FlippedTree.h"
#include "SuperPixel.h"

class Image {

    FlippedTreeNode* Pixels;
    int NumOfPixels;
    int ImageID;

    SuperPixel* FindSP(int pixel,FlippedTreeNode*& root);

public:

    Image(int pixels);
    Image(int ImageID,int pixels);
    ~Image();
    void SetScore(int pixel,int label,int score);
    void DeleteLabel(int pixel,int label);
    int GetHighestScoredLabel(int pixel);
    void UniteSuperPixels(int pixel1,int pixel2);
    int GetID() const;
    void SetID(int ID);

    class SameSPException{};
};


#endif //IMAGE_H
