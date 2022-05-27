/*
  ==============================================================================

    FileHandler.h
    Created: 23 May 2022 1:18:45am
    Author:  Fernando

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class FileHandler
{
public:
    FileHandler();
    ~FileHandler();

    juce::File getIRFolder();
    juce::File getIRFromIRFolder(juce::String IRFileName);
private:
    juce::String systemSeparator;
};