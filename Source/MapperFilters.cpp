/*
  ==============================================================================

    MapperFilters.cpp
    Created: 10 Jun 2022 1:07:49am
    Author:  Fernando

  ==============================================================================
*/

#include "MapperFilters.h"

double logspace(double start, double stop, int n, int N)
// start - start frequency
// stop - stop frequency
// n - the point which you wish to compute (zero based)
// N - the number of points over which to divide the frequency
// range.
//logspace(20, 200000, 0, 4) = 20
//logspace(20, 200000, 1, 4) = 200
//logspace(20, 200000, 2, 4) = 2000
//logspace(20, 200000, 3, 4) = 20000
{

    return start * pow(stop / start, n / (double)(N - 1));
}

float LPFilterMapper::normalMap(float inValue)
{
    //return juce::jmap(inValue, 0.0f, 100.0f, 20.0f, 20000.0f);
    //DBG("lagspace");
    int log_space_point = static_cast<int>(inValue);
    double logSpaceValue = logspace(20.0f, 4000.0f, log_space_point, 100);
    return static_cast<float>(logSpaceValue);
}


float HPFilterMapper::normalMap(float inValue)
{
    return juce::jmap(inValue, 0.0f, 100.0f, 20.0f, 20000.0f);
}




