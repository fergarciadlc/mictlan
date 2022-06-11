/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
MictlanAudioProcessor::MictlanAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", juce::AudioChannelSet::stereo(), true)
                     #endif
                       ), apvts(*this, nullptr, "parameters", createParameters())
#endif
{
}

MictlanAudioProcessor::~MictlanAudioProcessor()
{
}

//==============================================================================
juce::AudioProcessorValueTreeState::ParameterLayout MictlanAudioProcessor::createParameters()
{
    juce::AudioProcessorValueTreeState::ParameterLayout parameters;

    //parameters.add(std::make_unique<juce::AudioParameterBool>(
    //    "conv_bypass",
    //    "conv_bypass",
    //    false));
    //parameters.add(std::make_unique<juce::AudioParameterBool>(
    //    "dist_bypass",
    //    "dist_bypass",
    //    false));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(
        "dist_gain",
        "dist_gain",
        10.0f,
        100.0f,
        10.0f));
    //parameters.add(std::make_unique<juce::AudioParameterInt>(
    //    "dist_selection",
    //    "distortion_selection",
    //    0, 
    //    1, 
    //    0));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(
        "lp_cutoff",
        "lp_cutoff",
        juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.23f),
        20000.0f));        

    parameters.add(std::make_unique<juce::AudioParameterFloat>(
        "hp_cutoff",
        "hp_cutoff",
        juce::NormalisableRange<float>(20.0f, 20000.0f, 1.0f, 0.3f),
        20.0f));


    parameters.add(std::make_unique<juce::AudioParameterFloat>(
        "rb_room_size",
        "rb_room_size",
        juce::NormalisableRange<float>(0.0f, 1.0f),
        0.5f
        ));
    parameters.add(std::make_unique<juce::AudioParameterFloat>(
        "rb_damping",
        "rb_damping",
        juce::NormalisableRange<float>(0.0f, 1.0f),
        0.5f
        ));

    parameters.add(std::make_unique<juce::AudioParameterFloat>(
        "tension",
        "tension",
        0.0f,
        100.0f,
        0.0f));

    return parameters;
}


//==============================================================================
const juce::String MictlanAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool MictlanAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool MictlanAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool MictlanAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double MictlanAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int MictlanAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int MictlanAudioProcessor::getCurrentProgram()
{
    return 0;
}

void MictlanAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String MictlanAudioProcessor::getProgramName (int index)
{
    return {};
}

void MictlanAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void MictlanAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    //convolution.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
    lowPassFilter.prepare(sampleRate, 
                          samplesPerBlock, 
                          getTotalNumInputChannels(), 
                          lowPassFilter.lowPassType, 
                          1000.0f);
    highPassFilter.prepare(sampleRate,
                           samplesPerBlock,
                           getTotalNumInputChannels(),
                           lowPassFilter.highPassType,
                           1000.0f);

    juceReverb.prepare(sampleRate, samplesPerBlock, getTotalNumInputChannels());
}

void MictlanAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool MictlanAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    juce::ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    // Some plugin hosts, such as certain GarageBand versions, will only
    // load plugins that support stereo bus layouts.
    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void MictlanAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
    juce::ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    float tension_value = apvts.getRawParameterValue("tension")->load();
    float distValue = valueMapper.mapDistortion(tension_value, "normal");
    float hpFreqValue = valueMapper.mapLPFilter(tension_value, "normal");
    float rbRoomSize = valueMapper.mapReverbRoomSize(tension_value, "normal");

    //convolution.process(buffer, apvts.getRawParameterValue("conv_bypass")->load()); 
    distortion.process(
        buffer, 
        //apvts.getRawParameterValue("dist_gain")->load(),
        distValue,
        //apvts.getRawParameterValue("dist_selection")->load(),
        0,
        //apvts.getRawParameterValue("dist_bypass")->load()
        false
    ); // ok

    // OK :D 
    lowPassFilter.updateFilter(20000.0f);
    lowPassFilter.process(buffer);

    highPassFilter.updateFilter(hpFreqValue);
    highPassFilter.process(buffer);
    
    juceReverb.updateReverb(rbRoomSize,
                            apvts.getRawParameterValue("rb_damping")->load());
    juceReverb.process(buffer);

}

//==============================================================================
bool MictlanAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* MictlanAudioProcessor::createEditor()
{
    return new MictlanAudioProcessorEditor (*this);
}

//==============================================================================
void MictlanAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void MictlanAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new MictlanAudioProcessor();
}
