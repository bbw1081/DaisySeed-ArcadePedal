#include "ChorusEffect.h"

void ChorusEffect::Init(float sample_rate){
    chorus_.Init(sample_rate);
    chorus_.SetFeedback(0);
    SetParams(0.5, 0.5);
}

float ChorusEffect::Process(float in){ return chorus_.Process(in); }

void ChorusEffect::SetParams(float x, float y){
    chorus_.SetDelay(x);
    chorus_.SetLfoDepth(y);
}

const char* ChorusEffect::GetName(){
    return "Chorus";
}