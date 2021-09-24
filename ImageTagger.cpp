#include "ImageTagger.h"

ImageTagger::ImageTagger(int pixels):images(new Image*[Size]), deletedArray(new bool[Size]){
    CurrentTotalImages = 0;
    TotalPixels = pixels;
    for(int i = 0; i < Size;i++){
        images[i] = nullptr;
        deletedArray[i] = false;
    }
}

ImageTagger::~ImageTagger() {
    delete[] images;
    delete[] deletedArray;
}

void ImageTagger::InsertImage(int ImageID) {

    InsertHash(ImageID,new Image(TotalPixels));

    if(CurrentTotalImages/Size > ResizeRatio){
        Image** NewArray = new Image*[]
    }

}

void ImageTagger::InsertHash(int key,Image* image) {
    int HashFunction = key%Size;
    int StepFunction = 1+(key%5);
    int k = 0;
    while(1){
        int index = HashFunction+k*StepFunction;
        if(images[index] == nullptr){
            deletedArray[index] = false;
            images[index] = image;
            CurrentTotalImages++;
            break;
        }
        k++;
    }
}