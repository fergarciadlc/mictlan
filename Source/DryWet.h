/*
  ==============================================================================

    DryWet.h
    Created: 27 May 2022 1:40:50am
    Author:  Fernando

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DryWet
{
public:
    
    DryWet();
    ~DryWet();
    
    void process(juce::AudioBuffer<float>& inBufferWet,
                 juce::AudioBuffer<float>& inBufferDry,
                 float inDryWet);
};
