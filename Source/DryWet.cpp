/*
  ==============================================================================

    DryWet.cpp
    Created: 27 May 2022 1:40:50am
    Author:  Fernando

  ==============================================================================
*/

#include "DryWet.h"

DryWet::DryWet(){}
DryWet::~DryWet(){}

void DryWet::process(juce::AudioBuffer<float>& inBufferWet,
                     juce::AudioBuffer<float>& inBufferDry,
                     float inDryWet)
{
    inDryWet = (inDryWet/100.0f);
    
    for(int channel = 0; channel < inBufferWet.getNumChannels(); channel++)
    {
        for(int i = 0; i < inBufferWet.getNumSamples(); i++)
        {
            float wet = inBufferWet.getSample(channel, i);
            float dry = inBufferDry.getSample(channel, i);
            float out = dry * (1.0f - inDryWet) + (inDryWet * wet);
            
            inBufferWet.setSample(channel, i, out);
        }
    }
}
