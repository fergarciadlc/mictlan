/*
  ==============================================================================

    Mapper.cpp
    Created: 4 Jun 2022 2:20:48am
    Author:  Fernando

  ==============================================================================
*/

#include "Mapper.h"

ValueMapper::ValueMapper() {}
ValueMapper::~ValueMapper() {}


float ValueMapper::mapLPFilter(float inValue, juce::String preset)
{
    return lpMapper.normalMap(inValue);
}

float ValueMapper::mapHPFilter(float inValue, juce::String preset)
{
    return hpMapper.normalMap(inValue);
}

float ValueMapper::mapDistortion(float inValue, juce::String preset)
{
    return distMapper.normalMap(inValue);
}

float ValueMapper::mapReverbRoomSize(float inValue, juce::String preset)
{
    return rbMapper.normalMapRoomSize(inValue);
}

float ValueMapper::mapReverbDamping(float inValue, juce::String preset)
{
    return rbMapper.normalMapDamping(inValue);
}

