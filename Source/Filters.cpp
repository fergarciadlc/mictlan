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

//void Filters::reset()
//{
//    genericFilter.reset();
//}

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

    //genericFilter.prepare(spec);
    //genericFilter.setCutoffFrequency(cutoffFrequency);
    //genericFilter.setType(filterType);
    genericFilter.reset();
    updateFilter(cutoffFrequency);
    genericFilter.prepare(spec);
    genericFilter.setCutoffFrequency(cutoffFrequency);
    genericFilter.setType(filterType);
}

void Filters::updateFilter(float cutoffFrequency)
{
    genericFilter.setCutoffFrequency(cutoffFrequency);
}

void Filters::process(juce::AudioBuffer<float> inBuffer)
{
    auto audioBlock = juce::dsp::AudioBlock<float>(inBuffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    genericFilter.process(context);
}

// =======================================================

FIRFilter::FIRFilter() {}
FIRFilter::~FIRFilter() {}

void FIRFilter::prepare(double inSampleRate,
                        int inSamplesPerBlock,
                        int inNumChannels,
                        float cutoffFrequency,
                        size_t filterOrder)
{
    juce::dsp::ProcessSpec spec{};
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inNumChannels;

    sampleRate = inSampleRate;
    samplesPerBlock = inSamplesPerBlock;
    numChannels = inNumChannels;
    //order = filterOrder;

    genericFilter.reset();
    updateFilter(cutoffFrequency, filterOrder);
    genericFilter.prepare(spec);
    

}

void FIRFilter::updateFilter(float cutoffFrequency, size_t filterOrder)
{
    *genericFilter.state = *juce::dsp::FilterDesign<float>::designFIRLowpassWindowMethod(
        cutoffFrequency,
        sampleRate, 
        filterOrder,
        juce::dsp::WindowingFunction<float>::blackmanHarris
    );
}

void FIRFilter::process(juce::AudioBuffer<float> inBuffer)
{
    auto audioBlock = juce::dsp::AudioBlock<float>(inBuffer);
    auto context = juce::dsp::ProcessContextReplacing<float>(audioBlock);
    genericFilter.process(context);
}


