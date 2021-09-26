#include "library.h"
#include "ImageTagger.h"
#include "iostream"

void * Init(int pixels){

    try{
        auto* DS = new ImageTagger(pixels);
        return (void *)DS;
    }catch(...){
        return nullptr;
    }

}

StatusType AddImage(void *DS, int imageID){

    if(!DS || imageID <= 0)
        return INVALID_INPUT;
    try{
        ((ImageTagger*)DS)->InsertImage(imageID);
        return SUCCESS;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
}

StatusType DeleteImage(void *DS, int imageID){

    if(!DS || imageID <= 0)
        return INVALID_INPUT;
    try{
        ((ImageTagger*)DS)->removeImage(imageID);
        return SUCCESS;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }
}

StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score){

    if(!DS || imageID <= 0 || pixel < 0 || score <= 0 || label <= 0)
        return INVALID_INPUT;
    if(((ImageTagger*)DS)->GetNumOfPixels() <= pixel)
        return INVALID_INPUT;
    try{
        ((ImageTagger*)DS)->SetImageLabelScore(imageID,pixel,label,score);
        return SUCCESS;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }

}

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label){

    if(!DS || imageID <= 0 || pixel < 0 || label <= 0)
        return INVALID_INPUT;
    if(((ImageTagger*)DS)->GetNumOfPixels() <= pixel)
        return INVALID_INPUT;
    try{
        ((ImageTagger*)DS)->RemoveLabel(imageID,pixel,label);
        return SUCCESS;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }

}

StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label){

    if(!DS || imageID <= 0 || pixel < 0 || !label)
        return INVALID_INPUT;
    if(((ImageTagger*)DS)->GetNumOfPixels() <= pixel)
        return INVALID_INPUT;
    try{
        *label = ((ImageTagger*)DS)->GetHighestScore(imageID,pixel);
        return SUCCESS;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }

}

StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2){

    if(!DS || imageID <= 0 || pixel1 < 0 || pixel2 < 0)
        return INVALID_INPUT;
    if(((ImageTagger*)DS)->GetNumOfPixels() <= pixel1 || ((ImageTagger*)DS)->GetNumOfPixels() <= pixel2)
        return INVALID_INPUT;
    try{
        ((ImageTagger*)DS)->MergeSuperPixels(imageID,pixel1,pixel2);
        return SUCCESS;
    }catch (std::bad_alloc& e){
        return ALLOCATION_ERROR;
    }catch(...){
        return FAILURE;
    }

}

void Quit(void** DS){

    if(!DS)
        return;
    delete *(ImageTagger**)DS;
    *DS = nullptr;

}