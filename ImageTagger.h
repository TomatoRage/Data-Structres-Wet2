#ifndef IMAGETAGGER_H
#define IMAGETAGGER_H

#include "Image.h"

class ImageTagger {
    Image** images;
    bool* deletedArray;
    int Size = 31;
    int TotalPixels;
    int CurrentTotalImages;
    const int ResizeRatio = 0.75;

    void InsertHash(int key,Image* image);

public:
    ImageTagger(int pixels);
    ~ImageTagger();
    void InsertImage(int ImageID);
    void removeImage(int ImageID);
    void SetImageLabelScore(int ImageID,int pixel,int label,int score);
    void RemoveLabel(int ImageID,int pixel,int label);
    int GetHighestScore(int ImageID,int pixel);
    void MergeSuperPixels(int ImageID,int pixel1,int pixel2);

    class ImageAlreadyExistsException{};
};


#endif //IMAGETAGGER_H
