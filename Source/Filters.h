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

    void updateFilter(float cutoffFrequency);

    juce::dsp::StateVariableTPTFilterType lowPassType;
    juce::dsp::StateVariableTPTFilterType highPassType;
private:
    juce::dsp::StateVariableTPTFilter<float> genericFilter;
    
};


class FIRFilter
{
public:
    FIRFilter();
    ~FIRFilter();

    void prepare(double inSampleRate, 
                 int inSamplesPerBlock, 
                 int inNumChannels,
                 float cutoffFrequency,
                 size_t filterOrder);
    void process(juce::AudioBuffer<float> inBuffer);

    void updateFilter(float cutoffFrequency, size_t filterOrder);
private:
    juce::dsp::ProcessorDuplicator<juce::dsp::FIR::Filter<float>, juce::dsp::FIR::Coefficients<float>> genericFilter;

    //size_t order;
    double sampleRate;
    int samplesPerBlock;
    int numChannels;
};
