/*
  ==============================================================================

    MapperReverb.h
    Created: 10 Jun 2022 1:08:02am
    Author:  Fernando

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class ReverbMapper
{
public:
    ReverbMapper() {};
    ~ReverbMapper() {};

    float normalMapRoomSize(float inValue);
    float normalMapDamping(float inValue);

};
