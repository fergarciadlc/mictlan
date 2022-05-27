/*
  ==============================================================================

    Distortion.cpp
    Created: 27 May 2022 1:46:13am
    Author:  Fernando

  ==============================================================================
*/

#include "Distortion.h"

Distortion::Distortion(){}

Distortion::~Distortion(){}

void Distortion::process(juce::AudioBuffer<float> inBuffer, float inGain, int inType)
{
    for(int channel = 0; channel < inBuffer.getNumChannels(); channel++)
    {
        for(int i = 0; i < inBuffer.getNumSamples(); i++)
        {
            float sample = inBuffer.getSample(channel, i);
            float newInput = sample * (inGain / 10.0f);
            float out = 0.0f;
            
            switch(inType)
            {
                case 0:
                    // SOFT CLIPPING
                    if (newInput >= 1.0f)
                        out = 1.0f;
                    else if ((newInput > -1.0f) && (newInput < 1.0f))
                        out = (3.0f / 2.0f) * (newInput - (powf(newInput, 3.0f) / 3.0f));
                    else if (newInput <= -1.0f)
                        out = -1.0f;
                    
                    out = out * 0.5f;
                    break;
                    
                case 1:
                    // HARD CLIPPING
                    float threshold = 1.0f;
                    if(newInput > threshold)
                        out = threshold;
                    else if(newInput < -threshold)
                        out = -threshold;
                    else
                        out = newInput;
                    
                    break;
            }
            
            inBuffer.setSample(channel, i, out);
        }
    }
}
