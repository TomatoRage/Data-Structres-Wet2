#include "SuperPixel.h"

SuperPixel::SuperPixel():MaxScore(-1),MaxTag(-1) {}

void SuperPixel::InsertTag(int tag, int score) {
    int ExistingScore = -1;
    int TotalScore = score;
    try{
       ExistingScore = Tags.Find(tag);
    }catch(...){
        Tags.insert(tag,score);
    }

    if(ExistingScore != -1){
        TotalScore += ExistingScore;

        Tags.remove(tag);
        Tags.insert(tag,TotalScore);
    }


    if (MaxScore <= TotalScore){
        if (TotalScore == MaxScore){
            if(tag > MaxTag){
                MaxTag = tag;
            }
        }else{
            MaxTag = tag;
            MaxScore = TotalScore;
        }
    }
}

void SuperPixel::DeleteTag(int tag) {

    Tags.remove(tag);

    if(MaxTag == tag){

        int key;
        int* key_ptr = &key;

        Tags.ResetIterator();
        MaxScore = Tags.NextIteration(&key_ptr);

        for(int i = 0; i < Tags.GetSize()-1;i++){
            int Score = Tags.NextIteration(&key_ptr);
            if(Score > MaxScore){
                MaxScore = Score;
                MaxTag = key;
            }else if(Score == MaxScore){
                if(key > MaxTag)
                    MaxTag = key;
            }
        }

    }

}

int SuperPixel::GetMaxScore(int *score) const {
    *score = MaxScore;
    return MaxTag;
}

void SuperPixel::ResetIterator() {
     Tags.ResetIterator();
}

int SuperPixel::NextIteration(int *score) {
    int tag;
    int* tag_ptr = &tag;
    *score = Tags.NextIteration(&tag_ptr);
    return tag;
}

int SuperPixel::GetNumOfTags() {
    return Tags.GetSize();
}

void SuperPixel::MergeSuperPixel(SuperPixel* SP) {

    int tag,scoreToAdd,counter = 0,MergingSize = SP->GetNumOfTags();
    SP->ResetIterator();

    for(int i = 0; i < MergingSize;i++){
        tag = SP->NextIteration(&scoreToAdd);
        try{
            InsertTag(tag,scoreToAdd);
            counter ++;
        }catch(BST<int,int>::FailureException& e){
            int score = Tags.Find(tag);
            scoreToAdd += score;
            Tags.UpdateKey(tag,scoreToAdd);
        }
        if(scoreToAdd > MaxScore){
            MaxScore = scoreToAdd;
            MaxTag = tag;
        }
    }
    #warning("Fix complexity")
}