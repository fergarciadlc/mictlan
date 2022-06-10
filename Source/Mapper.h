/*
  ==============================================================================

    Mapper.h
    Created: 4 Jun 2022 2:20:48am
    Author:  Fernando

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "MapperFilters.h"
#include "MapperDistortion.h"
#include "MapperReverb.h"


class ValueMapper
{
public:
    ValueMapper();
    ~ValueMapper();

    float mapLPFilter(float inValue, juce::String preset = "normal");
    float mapHPFilter(float inValue, juce::String preset = "normal");
    float mapDistortion(float inValue, juce::String preset = "normal");
    float mapReverbRoomSize(float inValue, juce::String preset = "normal");
    float mapReverbDamping(float inValue, juce::String preset = "normal");
private:

    ReverbMapper rbMapper;
    DistortionMapper distMapper;
    LPFilterMapper lpMapper;
    HPFilterMapper hpMapper;
};

