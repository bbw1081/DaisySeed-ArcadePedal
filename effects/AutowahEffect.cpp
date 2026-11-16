#include "AutowahEffect.h"

void AutowahEffect::Init(float sample_rate){
    autowah_.Init(sample_rate);
    autowah_.SetLevel(0.0f);
    SetParams(0.5, 0.5);
}

float AutowahEffect::Process(float in){
    return autowah_.Process(in);
}

void AutowahEffect::SetParams(float x, float y){
    autowah_.SetDryWet(x);
    autowah_.SetWah(y);
}

const char* AutowahEffect::GetName(){
    return "Wah";
}