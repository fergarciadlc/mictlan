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
    setSize (250, 250);
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
    g.fillAll(juce::Colours::black);
    g.drawImageAt(juce::ImageCache::getFromMemory(BinaryData::bg_png, BinaryData::bg_pngSize), 0, 0);
    //g.drawImageAt(juce::ImageCache::getFromMemory(BinaryData::bg1_png, BinaryData::bg1_pngSize), 0, 0);
    //g.drawImageAt(juce::ImageCache::getFromMemory(BinaryData::bg3_png, BinaryData::bg3_pngSize), 0, 0);

    g.setColour (juce::Colours::white);
    g.setFont (20.0f);
    //g.drawFittedText ("MICTLAN", getLocalBounds(), juce::Justification::centredBottom, 1);
}

void MictlanAudioProcessorEditor::resized()
{
    float bigDiameter = 0.52f;
    slider.setBoundsRelative(0.5f - bigDiameter / 2, 0.5f - bigDiameter / 2, bigDiameter, bigDiameter);
}
