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
class DaFlangeAudioProcessorEditor  : public AudioProcessorEditor
{
public:
    DaFlangeAudioProcessorEditor (DaFlangeAudioProcessor&);
    ~DaFlangeAudioProcessorEditor();

    //==============================================================================
    void paint (Graphics&) override;
    void resized() override;

    Slider feedbackSlider;
    Label feedbackLabel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> feedbackAttachment;
    
    Slider widthSlider;
    Label widthLabel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> widthAttachment;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DaFlangeAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DaFlangeAudioProcessorEditor)
};
