/*
  ==============================================================================

    Filters.h
    Created: 27 May 2022 3:23:02am
    Author:  Fernando

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>


class Filters
{
public:
    Filters();
    ~Filters();

    void prepare(double inSampleRate, 
                 int inSamplesPerBlock, 
                 int inNumChannels, 
                 juce::dsp::StateVariableTPTFilterType filterType, 
                 float cutoffFrequency);
    void process(juce::AudioBuffer<float> inBuffer);

    juce::dsp::StateVariableTPTFilterType lowPassType;
    juce::dsp::StateVariableTPTFilterType highPassType;
private:
    juce::dsp::StateVariableTPTFilter<float> genericFilter;
    
};
