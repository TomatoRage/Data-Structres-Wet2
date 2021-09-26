#ifndef IMAGETAGGER_H
#define IMAGETAGGER_H

#include "Image.h"

class ImageTagger {
    Image** images;
    bool* deletedArray;
    int Size = 251;
    int TotalPixels;
    int CurrentTotalImages;
    int DeleteActionCounter;
    int HashFunctionMod = Size;
    const int RehashMultiplier = 1;
    const double ResizeRatio = 0.5;

    void InsertHash(int key,Image* image);
    int FindHash(int imageID);
    static int FindNextPrime(int start);

public:
    ImageTagger(int pixels);
    ~ImageTagger();
    void InsertImage(int ImageID);
    void removeImage(int ImageID);
    void SetImageLabelScore(int ImageID,int pixel,int label,int score);
    void RemoveLabel(int ImageID,int pixel,int label);
    int GetHighestScore(int ImageID,int pixel);
    void MergeSuperPixels(int ImageID,int pixel1,int pixel2);
    int GetNumOfPixels() const;

    class ImageAlreadyExistsException{};
    class ImageNotFoundException{};

};


#endif //IMAGETAGGER_H
