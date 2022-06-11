/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MictlanAudioProcessorEditor::MictlanAudioProcessorEditor (MictlanAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    sliderAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "tension", slider);
    slider.setSliderStyle(juce::Slider::SliderStyle::RotaryHorizontalVerticalDrag);
    slider.setTextBoxStyle(juce::Slider::TextEntryBoxPosition::NoTextBox, false, 0, 0);
    slider.setLookAndFeel(&lookAndFeel);
    addAndMakeVisible(slider);
    setSize (500, 300);
}

MictlanAudioProcessorEditor::~MictlanAudioProcessorEditor()
{
    slider.setLookAndFeel(nullptr);
}

//==============================================================================
void MictlanAudioProcessorEditor::paint (juce::Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (getLookAndFeel().findColour (juce::ResizableWindow::backgroundColourId));

    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    g.drawFittedText ("MICTLAN", getLocalBounds(), juce::Justification::centred, 1);
}

void MictlanAudioProcessorEditor::resized()
{
    slider.setBoundsRelative(0.5 - 0.2f, 0.5 - 0.2f, 0.4f, 0.4f);
}
