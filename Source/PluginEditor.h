/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"
#include "Knob.h"

//==============================================================================
/**
*/
class MictlanAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    MictlanAudioProcessorEditor (MictlanAudioProcessor&);
    ~MictlanAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    MictlanAudioProcessor& audioProcessor;

    juce::Slider slider;
    Knob_LookAndFeel lookAndFeel;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (MictlanAudioProcessorEditor)
};
