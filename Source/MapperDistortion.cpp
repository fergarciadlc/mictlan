/*
  ==============================================================================

    MapperDistortion.cpp
    Created: 10 Jun 2022 1:07:31am
    Author:  Fernando

  ==============================================================================
*/

#include "MapperDistortion.h"

float DistortionMapper::normalMap(float inValue)
{
    float proportion = 0.25;
    if (inValue < 10.0f ) { return 10.0f; }
    if (inValue * proportion < 10.0f) { return 10.0f; }
    return proportion * inValue;
}

