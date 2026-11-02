#pragma once

#include "daisy_seed.h"
#include "daisysp.h"
#include <stddef.h>
#include <string.h>

using namespace daisy;

/**
 * Interface for effect type classes
 * 
 * @author Richard Wilkinson
 */
class BaseEffect {
public:

    /* Destructor */
    virtual ~BaseEffect() {}

    /**
     * Initialize the effect
     * 
     * @param sample_rate audio sample rate
     */
    virtual void Init(float sample_rate) = 0;

    /**
     * Processes the audio
     * 
     * @param in audio sample input
     * 
     * @return the processed audio
     */
    virtual float Process(float in) = 0;

    /**
     * Set the effect parameters based on the x and y
     * inputs from the joystick
     * 
     * @param x joystick x, float from 0-1
     * @param y joystick y, float from 0-1
     */
    virtual void SetParams(float x, float y) = 0;

    /**
     * Get the name of the effect
     * 
     * @return The name of the effect
     */
    virtual const char* GetName() = 0;
};