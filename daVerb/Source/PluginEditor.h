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

    Slider dampingSlider;
    Label dampingLabel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> dampingAttachment;

    Slider widthSlider;
    Label widthLabel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> widthAttachment;

    Slider wetLevelSlider;
    Label wetLevelLabel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> wetLevelAttachment;

    Slider dryLevelSlider;
    Label dryLevelLabel;
    std::unique_ptr <AudioProcessorValueTreeState::SliderAttachment> dryLevelAttachment;

    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    DaVerbAudioProcessor& processor;

    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (DaVerbAudioProcessorEditor)
};
