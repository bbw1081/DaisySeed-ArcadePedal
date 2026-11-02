#include "FlangerEffect.h"

void FlangerEffect::Init(float sample_rate){
    flanger_.Init(sample_rate);
    flanger_.SetFeedback(0);
    SetParams(0.5, 0.5)
}

float FlangerEffect::Process(float in){ return flanger_.Process(in); }

void FlangerEffect::SetParams(float x, float y){
    flanger_.SetDelay(x);
    flanger_.SetLfoDepth(y);
}

const char* FlangerEffect::GetName(){
    return "Flanger";
}