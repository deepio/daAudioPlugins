/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.
    Same circular buffer as:
      https://github.com/ffAudio/ffTapeDelay/blob/2ef785c72acbbb0b21dfc9b2b85f3ecf292f0713/Source/TapeDelayProcessor.cpp#L178-L216

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"

#define FEEDBACK_ID "feedbackValue"
#define FEEDBACK_NAME "Feedback"
#define WIDTH_ID "widthValue"
#define WIDTH_NAME "Width"

//==============================================================================
/**
*/
class DaFlangeAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    DaFlangeAudioProcessor();
    ~DaFlangeAudioProcessor();

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
    void fillDelayBuffer(
      const int channel
      ,const int bufferLength
      ,const int delayBufferLength
      ,const float* bufferData
      ,const float inGain
      ,const float outGain
    );

    void fetchDelayBuffer(
      AudioBuffer<float>& buffer
      ,const int channel
      ,const int bufferLength
      ,const int delayBufferLength
      ,const float* delayBufferData
    );

    void feedbackDelay(
      const int channel
      ,const int bufferLength
      ,const int delayBufferLength
      ,float* dryBuffer
      ,const float inGain
      ,const float outGain
    );

    void updateSineBuffer();

    //==============================================================================
    AudioProcessorValueTreeState mParameterTree;

    AudioBuffer<float> mDelayBuffer;
    int mSampleRate {44100};
    int mWritePosition {0};

    float currentAngle = 0.0;
    float angleDelta = 0.0;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DaFlangeAudioProcessor)
};
