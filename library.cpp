#include "library.h"
#include "Image.h"

void * Init(int pixels){

}

StatusType AddImage(void *DS, int imageID){

}

StatusType DeleteImage(void *DS, int imageID){

}

StatusType SetLabelScore(void *DS, int imageID, int pixel, int label, int score){

}

StatusType ResetLabelScore(void *DS, int imageID, int pixel, int label){

}

StatusType GetHighestScoredLabel(void *DS, int imageID, int pixel, int *label){

}

StatusType MergeSuperPixels(void *DS, int imageID, int pixel1, int pixel2){

}

void Quit(void** DS){

}