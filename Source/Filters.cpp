/*
  ==============================================================================

    Filters.cpp
    Created: 27 May 2022 3:23:02am
    Author:  Fernando

  ==============================================================================
*/

#include "Filters.h"


Filters::Filters() 
{
    lowPassType = juce::dsp::StateVariableTPTFilterType::lowpass;
    highPassType = juce::dsp::StateVariableTPTFilterType::highpass;
}
Filters::~Filters(){}

void Filters::prepare(double inSampleRate, 
                      int inSamplesPerBlock, 
                      int inNumChannels, 
                      juce::dsp::StateVariableTPTFilterType filterType, 
                      float cutoffFrequency)
{
    juce::dsp::ProcessSpec spec{};
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inNumChannels;

    genericFilter.prepare(spec);
    genericFilter.setCutoffFrequency(cutoffFrequency);
    genericFilter.setType(filterType);
}

void Filters::process(juce::AudioBuffer<float> inBuffer)
{
    auto audioBlock = juce::dsp::AudioBlock<float>(inBuffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    genericFilter.process(context);
}
