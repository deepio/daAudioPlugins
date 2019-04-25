/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DaVerbAudioProcessor::DaVerbAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
,mParameterTree(*this, nullptr, "rPARAMETERS",
{
    std::make_unique<AudioParameterFloat>(ROOM_SIZE_ID, ROOM_SIZE_NAME, 0.0f, 1.0f, 0.8f)
    ,std::make_unique<AudioParameterFloat>(DAMPING_ID, DAMPING_NAME, 0.0f, 1.0f, 0.8f)
    ,std::make_unique<AudioParameterFloat>(WIDTH_ID, WIDTH_NAME, 0.0f, 1.0f, 0.8f)
    ,std::make_unique<AudioParameterFloat>(WET_LEVEL_ID, WET_LEVEL_NAME, 0.0f, 1.0f, 0.8f)
    ,std::make_unique<AudioParameterFloat>(DRY_LEVEL_ID, DRY_LEVEL_NAME, 0.0f, 1.0f, 0.8f)
})
#endif
{}

DaVerbAudioProcessor::~DaVerbAudioProcessor() {}

//==============================================================================
const String DaVerbAudioProcessor::getName() const {return JucePlugin_Name;}

bool DaVerbAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool DaVerbAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool DaVerbAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double DaVerbAudioProcessor::getTailLengthSeconds() const {return 0.0;}
int DaVerbAudioProcessor::getNumPrograms() {return 1;}
int DaVerbAudioProcessor::getCurrentProgram() {return 0;}
void DaVerbAudioProcessor::setCurrentProgram (int index) {}
const String DaVerbAudioProcessor::getProgramName (int index) {return {};}
void DaVerbAudioProcessor::changeProgramName (int index, const String& newName) {}

//==============================================================================
void DaVerbAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    auto channels = static_cast<uint32> (jmin (getMainBusNumInputChannels(), getMainBusNumOutputChannels()));
    dsp::ProcessSpec spec {sampleRate, static_cast<uint32> (samplesPerBlock), channels};
    updateParameters();
    reset();
}

void DaVerbAudioProcessor::releaseResources() {}

#ifndef JucePlugin_PreferredChannelConfigurations
bool DaVerbAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
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

void DaVerbAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    mReverb1Parameters.roomSize = *mParameterTree.getRawParameterValue(ROOM_SIZE_ID);
    mReverb1Parameters.damping = *mParameterTree.getRawParameterValue(DAMPING_ID);
    mReverb1Parameters.freezeMode = 0.0f;
    mReverb1Parameters.width = *mParameterTree.getRawParameterValue(WIDTH_ID);
    mReverb1Parameters.wetLevel = *mParameterTree.getRawParameterValue(WET_LEVEL_ID);
    mReverb1Parameters.dryLevel = *mParameterTree.getRawParameterValue(DRY_LEVEL_ID);
    mReverb1.setParameters(mReverb1Parameters);

    // In case we have more outputs than inputs, this code clears any output
    // channels that didn't contain input data, (because these aren't
    // guaranteed to be empty - they may contain garbage).
    // This is here to avoid people getting screaming feedback
    // when they first compile a plugin, but obviously you don't need to keep
    // this code if your algorithm always overwrites all the output channels.
//    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
    for (auto i = jmin(2, totalNumInputChannels); i < totalNumOutputChannels; i++)
        buffer.clear (i, 0, buffer.getNumSamples());
    
    updateParameters();
    dsp::AudioBlock<float> block(buffer);

    // This is the place where you'd normally do the guts of your plugin's
    // audio processing...
    // Make sure to reset the state if your inner loop is processing
    // the samples and the outer loop is handling the channels.
    // Alternatively, you can process the samples with the channels
    // interleaved by keeping the same state.
    if (totalNumInputChannels == 1)
    {
        auto firstChan = block.getSingleChannelBlock(0);
        
        //DSP Module
        process(dsp::ProcessContextReplacing<float> (firstChan));
        
        //Basic Module
        //mReverb1.processMono(buffer.getWritePointer(0), buffer.getNumSamples());
    }
    else
    {
        //DSP Module
        block = block.getSubsetChannelBlock(0,2);
        process(dsp::ProcessContextReplacing<float> (block));
        
        //Basic Module
        //mReverb1.processStereo(buffer.getWritePointer(0), buffer.getWritePointer(1), buffer.getNumSamples());
    }
}

//==============================================================================
bool DaVerbAudioProcessor::hasEditor() const {return true;}

AudioProcessorEditor* DaVerbAudioProcessor::createEditor(){return new DaVerbAudioProcessorEditor (*this);}

//==============================================================================
void DaVerbAudioProcessor::getStateInformation (MemoryBlock& destData) {}
void DaVerbAudioProcessor::setStateInformation (const void* data, int sizeInBytes) {}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter() {return new DaVerbAudioProcessor();}

//==============================================================================
void DaVerbAudioProcessor::prepare (const dsp::ProcessSpec& spec)
{
    sampleRate = spec.sampleRate;
    
    auto& gainUp = reverbChain.get<0>();
    gainUp.setGainDecibels (24);

    auto& reverbP = reverbChain.get<1>();
    reverbP.setParameters(mReverb1Parameters);
    reverbChain.prepare(spec);
}

void DaVerbAudioProcessor::process (const dsp::ProcessContextReplacing<float>& context)
{
    ScopedNoDenormals noDenormals;
    inputVolume.process (context);
    mReverb1.process(context);
    outputVolume.process (context);
}

void DaVerbAudioProcessor::reset()
{
    reverbChain.reset();
}

void DaVerbAudioProcessor::updateParameters()
{
    auto inputdB  = Decibels::decibelsToGain  (1.0f);
    auto outputdB = Decibels::decibelsToGain (5.0f);
    if (inputVolume .getGainLinear() != inputdB)     inputVolume.setGainLinear (inputdB);
    if (outputVolume.getGainLinear() != outputdB)   outputVolume.setGainLinear (outputdB);
}
