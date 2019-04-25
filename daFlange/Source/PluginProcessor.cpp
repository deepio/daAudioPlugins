/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.
    Same circular buffer as:
        https://github.com/ffAudio/ffTapeDelay/blob/2ef785c72acbbb0b21dfc9b2b85f3ecf292f0713/Source/TapeDelayProcessor.cpp#L178-L216

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DaFlangeAudioProcessor::DaFlangeAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
}

DaFlangeAudioProcessor::~DaFlangeAudioProcessor()
{
}

//==============================================================================
const String DaFlangeAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool DaFlangeAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DaFlangeAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DaFlangeAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DaFlangeAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int DaFlangeAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int DaFlangeAudioProcessor::getCurrentProgram()
{
    return 0;
}

void DaFlangeAudioProcessor::setCurrentProgram (int index)
{
}

const String DaFlangeAudioProcessor::getProgramName (int index)
{
    return {};
}

void DaFlangeAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void DaFlangeAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    const int delayBufferSize = 2 * (sampleRate + samplesPerBlock);
    mSampleRate = sampleRate;
    mDelayBuffer.setSize(getTotalNumInputChannels(), delayBufferSize, false, true);
    lfoBuffer();
}

void DaFlangeAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DaFlangeAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
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

void DaFlangeAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());

    //==============================================================================
    const int bufferLength = buffer.getNumSamples();
    const int delayBufferLength = mDelayBuffer.getNumSamples();
    
    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* dryChannelData = buffer.getWritePointer(channel);
        const float* bufferData = buffer.getReadPointer(channel);
        const float* delayBufferData = mDelayBuffer.getReadPointer(channel);

        // ..do something to the data...
    }
    
    mWritePosition += bufferLength;
    mWritePosition %= delayBufferLength;
}

//==============================================================================
bool DaFlangeAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* DaFlangeAudioProcessor::createEditor()
{
    return new DaFlangeAudioProcessorEditor (*this);
}

//==============================================================================
void DaFlangeAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void DaFlangeAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new DaFlangeAudioProcessor();
}

//==============================================================================
void DaFlangeAudioProcessor::fillDelayBuffer(
  const int channel
  ,const int bufferLength
  ,const int delayBufferLength
  ,const float* bufferData
  ,const float inGain
  ,const float outGain
){
    if (delayBufferLength > bufferLength + mWritePosition)
    {
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferLength, inGain, outGain);
    } else {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        mDelayBuffer.copyFromWithRamp(channel, mWritePosition, bufferData, bufferRemaining, inGain, outGain);
        mDelayBuffer.copyFromWithRamp(channel, 0, bufferData, bufferLength - bufferRemaining, inGain, outGain);
    }
}

void DaFlangeAudioProcessor::fetchDelayBuffer(
  AudioBuffer<float>& buffer
  ,const int channel
  ,const int bufferLength
  ,const int delayBufferLength
  ,const float* delayBufferData
){
    auto currentSample = static_cast<float>(std::sin(currentAngle));
    currentAngle += angleDelta;
    float delayTime = *mParameterTree.getRawParameterValue(TIME_ID) + ((*mParameterTree.getRawParameterValue(TIME_ID) * 0.05) * currentSample);
    const int readPosition = static_cast<int> (delayBufferLength + mWritePosition - (mSampleRate * delayTime / 1000.0f)) % delayBufferLength;

    if (delayBufferLength > bufferLength + readPosition)
    {
        buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferLength);
    } else {
        const int bufferRemaining = delayBufferLength - readPosition;
        buffer.copyFrom(channel, 0, delayBufferData + readPosition, bufferRemaining);
        buffer.copyFrom(channel, bufferRemaining, delayBufferData, bufferLength - bufferRemaining);
    }
}

void DaFlangeAudioProcessor::feedbackDelay(
  const int channel
  ,const int bufferLength
  ,const int delayBufferLength
  ,float* dryBuffer
  ,const float inGain
  ,const float outGain
){
    if (delayBufferLength > bufferLength + mWritePosition)
    {
        //Copy the main signal to the delayed singal, and the delayed signal with the main signal gets put out of the speakers,
        // instead of the other way around.
        mDelayBuffer.addFromWithRamp(channel, mWritePosition, dryBuffer, bufferLength, inGain, outGain);
    } else {
        const int bufferRemaining = delayBufferLength - mWritePosition;
        mDelayBuffer.addFromWithRamp(channel, bufferRemaining, dryBuffer, bufferRemaining, inGain, outGain);
        mDelayBuffer.addFromWithRamp(channel, 0, dryBuffer, bufferLength - bufferRemaining, inGain, outGain);
    }
}

