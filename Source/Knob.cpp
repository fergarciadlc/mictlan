/*
  ==============================================================================

    Knob.cpp
    Created: 11 Jun 2022 12:07:59am
    Author:  Fernando

  ==============================================================================
*/

#include "Knob.h"

Knob_LookAndFeel::Knob_LookAndFeel()
{
    // ROTAR IMAGEN
    knobImage = juce::ImageCache::getFromMemory(BinaryData::knobThree_png, BinaryData::knobThree_pngSize);
    // FILM STRIP
    //knobImage = juce::ImageCache::getFromMemory(BinaryData::knobTwo_png, BinaryData::knobTwo_pngSize);
}

Knob_LookAndFeel::~Knob_LookAndFeel(){
}

void Knob_LookAndFeel::drawRotarySlider(juce::Graphics& g,
                            int x, int y,
                            int width, int height,
                            float sliderPosProportional,
                            float rotaryStartAngle,
                            float rotaryEndAngle,
                            juce::Slider& slider)
{
    //// FILM STRIP--------------------------------------------
    //const int numFrames = knobImage.getHeight() / knobImage.getWidth();
    //const int frameIndex = (int)std::ceil(sliderPosProportional * (numFrames - 1));
    //
    //const float radius = fmin(width*0.5, height*0.5);
    //const float centreX = x + width * 0.5f;
    //const float centreY = y + height * 0.5f;
    //const float rx = centreX - radius;
    //const float ry = centreY - radius;
    //
    //g.drawImage(knobImage,
    //            rx,
    //            ry,
    //            2 * radius,
    //            2 * radius,
    //            0,
    //            frameIndex * knobImage.getWidth(),
    //            knobImage.getWidth(),
    //            knobImage.getWidth());
    //// FILM STRIP--------------------------------------------
    
    // ROTAR IMAGEN -*----------------------------------------------
    auto radius = (float) juce::jmin (width / 2, height / 2);
    auto centreX = (float) x + (float) width  * 0.5f;
    auto centreY = (float) y + (float) height * 0.5f;
    auto rx = centreX - radius;
    auto ry = centreY - radius;
    
    //Rotating knob image equation
    float stopValue = 0.75f;
    float rotation = stopValue * juce::MathConstants<float>::twoPi * (sliderPosProportional - 0.5f);
    knobImage = knobImage.rescaled((int)radius * 2,
                                             (int)radius * 2,
                                             juce::Graphics::ResamplingQuality::highResamplingQuality);
    g.drawImageTransformed(knobImage, juce::AffineTransform::rotation(rotation,
                                                                      static_cast<float>(knobImage.getWidth() / 2),
                                                                      static_cast<float>(knobImage.getHeight() / 2)).translated(rx, ry));
    // ROTAR IMAGEN -*----------------------------------------------
}
