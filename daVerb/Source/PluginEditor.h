/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class DaVerbAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DaVerbAudioProcessorEditor (DaVerbAudioProcessor&);
    ~DaVerbAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

private:
    Slider roomSizeSlider;
    Label roomSizeLabel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> roomSizeAttachment;
    
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DaVerbAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DaVerbAudioProcessorEditor)
};
