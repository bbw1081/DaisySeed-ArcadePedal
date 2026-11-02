#pragma once

#include "BaseEffect.h"

class FlangerEffect : public BaseEffect {
public:

    void Init(float sample_rate) override;

    float Process(float in) override;

    void SetParams(float x, float y) override;

    const char* GetName() override;

private:
    daisysp::Flanger flanger_;
};