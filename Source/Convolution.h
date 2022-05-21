/*
  ==============================================================================

    Convolution.h
    Created: 21 May 2022 12:57:40pm
    Author:  Fernando

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Convolution
{
public:

    Convolution();
    ~Convolution();

    void prepare(double inSampleRate, int inSamplesPerBlock, int inNumChannels);

    void process(juce::AudioBuffer<float> inBuffer);

private:

    juce::dsp::Convolution conv;
    juce::File IRFile;

};