/*
  ==============================================================================

    MapperFilters.h
    Created: 10 Jun 2022 1:07:49am
    Author:  Fernando

  ==============================================================================
*/

#pragma once
#include<JuceHeader.h>

class LPFilterMapper
{
public:
    LPFilterMapper() {};
    ~LPFilterMapper() {};

    float normalMap(float inValue);
};

class HPFilterMapper
{
public:
    HPFilterMapper() {};
    ~HPFilterMapper() {};

    float normalMap(float inValue);
};