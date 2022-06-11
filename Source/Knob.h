/*
  ==============================================================================

    Knob.h
    Created: 11 Jun 2022 12:07:59am
    Author:  Fernando

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class Knob_LookAndFeel : public juce::LookAndFeel_V4
{
public:
    
    Knob_LookAndFeel();
    ~Knob_LookAndFeel();
    
    void drawRotarySlider(juce::Graphics& g,
                          int x, int y,
                          int width, int height,
                          float sliderPosProportional,
                          float rotaryStartAngle,
                          float rotaryEndAngle,
                          juce::Slider& slider) override;

private:
    
    juce::Image knobImage;
    
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (Knob_LookAndFeel)
};
