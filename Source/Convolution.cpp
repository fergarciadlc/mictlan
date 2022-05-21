/*
  ==============================================================================

    Convolution.cpp
    Created: 21 May 2022 12:57:40pm
    Author:  Fernando

  ==============================================================================
*/

#include "Convolution.h"

Convolution::Convolution() {}

Convolution::~Convolution() {}

void Convolution::prepare(double inSampleRate, int inSamplesPerBlock, int inNumChannels)
{
    // load IR file from local wav
    // GET PATH PARA IMPULSO
    //************************************ DIRECTORY SEPARATORS ************************************//
    #if JUCE_WINDOWS
        static const juce::String directorySeparator = "\\";
    #elif JUCE_MAC
        static const juce::String directorySeparator = "/";
    #endif

    auto impulsePath = (juce::File::getSpecialLocation(juce::File::userDesktopDirectory)).getFullPathName() + directorySeparator + "impulse.wav";
    IRFile = juce::File(impulsePath);

    // initialise spect
    juce::dsp::ProcessSpec spec;
    spec.sampleRate = inSampleRate;
    spec.maximumBlockSize = inSamplesPerBlock;
    spec.numChannels = inNumChannels;

    // start convolution
    conv.reset();
    conv.prepare(spec);

    // load IR
    conv.loadImpulseResponse(IRFile.getFullPathName(),
        juce::dsp::Convolution::Stereo::no,
        juce::dsp::Convolution::Trim::yes,
        IRFile.getSize()
    );


}

void Convolution::process(juce::AudioBuffer<float> inBuffer)
{
    juce::dsp::AudioBlock<float> block(inBuffer);
    juce::dsp::ProcessContextReplacing<float> context(block);
    conv.process(context);
}

