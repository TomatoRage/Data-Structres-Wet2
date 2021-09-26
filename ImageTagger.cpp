#include "ImageTagger.h"

ImageTagger::ImageTagger(int pixels){
    images = new Image*[Size];
    deletedArray = new bool[Size];
    CurrentTotalImages = 0;
    DeleteActionCounter = 0;
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

    if(double(CurrentTotalImages)/double(Size) > ResizeRatio){
        int size = FindNextPrime(Size*2);
        auto** NewArray = new Image*[size];
        auto* newDeleteArray = new bool[size];

        for(int i = 0; i < size; i++){
            NewArray[i] = nullptr;
            newDeleteArray[i] = false;
        }

        for(int i = 0; i < Size; i++){
            NewArray[i] = images[i];
            newDeleteArray[i] = deletedArray[i];
        }


        delete[] images;
        delete[] deletedArray;

        images = NewArray;
        deletedArray = newDeleteArray;
        Size = size;
    }

}

void ImageTagger::removeImage(int ImageID) {

    int index = FindHash(ImageID);

    if(index == -1)
        throw ImageNotFoundException();

    delete images[index];
    images[index] = nullptr;
    deletedArray[index] = true;
    DeleteActionCounter++;

    if(DeleteActionCounter >= RehashMultiplier*Size){
        auto** NewArray = new Image*[Size];
        DeleteActionCounter = 0;
        HashFunctionMod = Size;
        for(int i=0; i < Size; i++){
            NewArray[i] = nullptr;
            deletedArray[i] = false;
        }
        for(int i=0; i < Size; i++){
            if(images[i] != nullptr){
                int ID = images[i]->GetID();
                int HashFunction = ID%HashFunctionMod;
                int StepFunction = 1+(ID%5);
                int k = 0;
                int HashIndex = (HashFunction+k*StepFunction) % Size;

                while(true){
                    if(NewArray[HashIndex] == nullptr){
                        NewArray[HashIndex] = images[i];
                        break;
                    }
                    k++;
                }

            }
            deletedArray[i] = false;
        }
    }
}

void ImageTagger::SetImageLabelScore(int ImageID, int pixel, int label, int score) {
    int index = FindHash(ImageID);

    if(index == -1)
        throw ImageNotFoundException();
    images[index]->SetScore(pixel,label,score);
}

void ImageTagger::RemoveLabel(int ImageID, int pixel, int label) {
    int index = FindHash(ImageID);

    if(index == -1)
        throw ImageNotFoundException();
    images[index]->DeleteLabel(pixel,label);

}

int ImageTagger::GetHighestScore(int ImageID, int pixel) {
    int index = FindHash(ImageID);

    if(index == -1)
        throw ImageNotFoundException();

   return images[index]->GetHighestScoredLabel(pixel);
}

void ImageTagger::MergeSuperPixels(int ImageID, int pixel1, int pixel2) {
    int index = FindHash(ImageID);

    if(index == -1)
        throw ImageNotFoundException();

    images[index]->UniteSuperPixels(pixel1,pixel2);
}

void ImageTagger::InsertHash(int key,Image* image) {
    int HashFunction = key%HashFunctionMod;
    int StepFunction = 1+(key%5);
    int k = 0;
    while(true){
        int index = (HashFunction+k*StepFunction) % Size;
        if(images[index] == nullptr){
            deletedArray[index] = false;
            images[index] = image;
            image->SetID(key);
            CurrentTotalImages++;
            return;
        }
        else if(images[index]->GetID() == key)
            throw ImageAlreadyExistsException();
        k++;
    }
}

int ImageTagger::FindNextPrime(int start) {
    int PrimeContainer[start];
    int size = 1;
    int i = 3;
    PrimeContainer[0] = 2;
    while(true){
        int isPrime = true;
        for(int j = 0; j < size; j++){
            if(i % PrimeContainer[j] == 0){
                isPrime = false;
                break;
            }
        }
        if(isPrime) {
            PrimeContainer[size] = i;
            size++;
            if(i > start)
                return i;
        }
        i += 2 ;
    }
}

int ImageTagger::FindHash(int imageID) {

    int HashFunction = imageID%HashFunctionMod;
    int StepFunction = 1+(imageID%5);
    int k = 0;

    while(true){
        int index = (HashFunction+k*StepFunction) % Size;
        if(images[index] == nullptr && !deletedArray[index]){
            return -1;
        }
        else if(images[index] != nullptr){
            if(images[index]->GetID() == imageID)
                return index;
        }
        k++;
    }
}

int ImageTagger::GetNumOfPixels() const {
    return TotalPixels;
}