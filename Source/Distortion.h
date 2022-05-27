/*
  ==============================================================================

    Distortion.h
    Created: 27 May 2022 1:46:13am
    Author:  Fernando

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Distortion
{
public:
    
    Distortion();
    ~Distortion();
    void process(juce::AudioBuffer<float> inBuffer, float inGain, int inType);
    
};