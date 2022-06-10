/*
  ==============================================================================

    MapperDistortion.h
    Created: 10 Jun 2022 1:07:31am
    Author:  Fernando

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class DistortionMapper
{
public:
    DistortionMapper() {};
    ~DistortionMapper() {};

    float normalMap(float inValue);
};
