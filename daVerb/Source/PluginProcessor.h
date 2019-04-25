/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define ROOM_SIZE_ID "roomSize"
#define ROOM_SIZE_NAME "Room Size"
#define DAMPING_ID "damping"
#define DAMPING_NAME "Damping"
#define WIDTH_ID "width"
#define WIDTH_NAME "Width"
#define WET_LEVEL_ID "wetLevel"
#define WET_LEVEL_NAME "Wet"
#define DRY_LEVEL_ID "drySize"
#define DRY_LEVEL_NAME "Dry"

//==============================================================================
/**
*/
class DaVerbAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DaVerbAudioProcessor();
    ~DaVerbAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

    //==============================================================================
    AudioProcessorValueTreeState mParameterTree;
    
    dsp::Reverb mReverb1;
    dsp::Reverb::Parameters mReverb1Parameters;
    
    //==============================================================================
    void prepare (const dsp::ProcessSpec& spec);
    void process (const dsp::ProcessContextReplacing<float>& context);
    void reset() override;
    void updateParameters();
    
    using GainProcessor   = dsp::Gain<float>;
    using ReverbProcessor = dsp::Reverb;

    dsp::ProcessorChain<GainProcessor, ReverbProcessor> overdrive;
    dsp::Gain<float> inputVolume, outputVolume;

    double sampleRate = 0.0;
    
private:
    //Reverb mReverb1;
    //Reverb::Parameters mReverb1Parameters;
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DaVerbAudioProcessor)
};
