#include "Image.h"

Image::Image(int pixels):Pixels(new FlippedTreeNode[pixels]),NumOfPixels(pixels) {
    for(int i = 0; i < pixels; i++){
        Pixels[i].father = nullptr;
        Pixels[i].index = i;
        Pixels[i].SP = new SuperPixel;
        Pixels[i].TotalSons = 0;
        ImageID = -1;
    }
}

Image::Image(int ImageID,int pixels):Pixels(new FlippedTreeNode[pixels]),NumOfPixels(pixels),ImageID(ImageID) {
    for(int i = 0; i < pixels; i++){
        Pixels[i].father = nullptr;
        Pixels[i].index = i;
        Pixels[i].SP = new SuperPixel;
        Pixels[i].TotalSons = 0;
    }
}

Image::~Image() {
    for(int i = 0; i < NumOfPixels; i++){
        delete Pixels[i].SP;
    }
    delete[] Pixels;
}

SuperPixel *Image::FindSP(int pixel,FlippedTreeNode*& root) {

    if(Pixels[pixel].father == nullptr){
        root = &Pixels[pixel];
        return Pixels[pixel].SP;
    }
    else if(Pixels[pixel].father->father == nullptr){
        root = Pixels[pixel].father;
        return Pixels[pixel].father->SP;
    }else{
        FlippedTreeNode* Node,*Temp,* Root = nullptr;

        Node = &Pixels[pixel];
        for(int i = 0; i < NumOfPixels; i++){
            if(Root)
                break;
            if(Node->father == nullptr)
                Root = Node;
            Node = Node->father;
        }
        Node = &Pixels[pixel];
        for(int i = 0; i < NumOfPixels; i++){
            if(Node->father == nullptr)
                break;
            Temp = Node;
            Node -= i;
            Node = Node->father;
            Temp->father = Root;
        }
        root = Root;
        return Root->SP;
    }
}

void Image::SetScore(int pixel, int label, int score) {
    FlippedTreeNode* root;
    SuperPixel* SP= FindSP(pixel,root);
    SP->InsertTag(label,score);
}

void Image::DeleteLabel(int pixel, int label) {
    FlippedTreeNode* root;
    SuperPixel* SP = FindSP(pixel,root);
    SP->DeleteTag(label);
}

int Image::GetHighestScoredLabel(int pixel) {
    int score;
    FlippedTreeNode* root;
    SuperPixel* SP = FindSP(pixel,root);
    return SP->GetMaxScore(&score);
}

void Image::UniteSuperPixels(int pixel1, int pixel2) {
    FlippedTreeNode* HostRoot,*OtherRoot;
    SuperPixel* Host = FindSP(pixel1,HostRoot);
    SuperPixel* ToBeUnited= FindSP(pixel2,OtherRoot);

    if(Host == ToBeUnited)
        throw SameSPException();
    if(OtherRoot->TotalSons > HostRoot->TotalSons){
        SuperPixel* Temp = Host;
        FlippedTreeNode* tempRoot = HostRoot;

        OtherRoot = HostRoot;
        HostRoot = tempRoot;

        Host = ToBeUnited;
        ToBeUnited = Temp;
    }
    Host->MergeSuperPixel(ToBeUnited);
    OtherRoot->SP = nullptr;
    OtherRoot->father = HostRoot;
    HostRoot->TotalSons += OtherRoot->TotalSons+1;

}

int Image::GetID() const {
    return ImageID;
}

void Image::SetID(int ID) {
    ImageID = ID;
}