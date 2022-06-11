/*
  ==============================================================================

    MapperReverb.cpp
    Created: 10 Jun 2022 1:08:02am
    Author:  Fernando

  ==============================================================================
*/

#include "MapperReverb.h"

float ReverbMapper::normalMapRoomSize(float inValue)
{
    return 1.0f * inValue / 100.0f;
}

float ReverbMapper::normalMapDamping(float inValue)
{
    return 1.0f * inValue;
}
