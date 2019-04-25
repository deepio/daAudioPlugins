/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DaFlangeAudioProcessorEditor::DaFlangeAudioProcessorEditor (DaFlangeAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);

    const int sliderBoxWidth = 50;
    const int sliderBoxHeight= 20;


    addAndMakeVisible(timeSlider);
    timeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    timeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    addAndMakeVisible(timeLabel);
    timeLabel.setText(TIME_NAME, dontSendNotification);
    timeLabel.setJustificationType(Justification::centred);
    timeLabel.attachToComponent(&timeSlider, false);
    addAndMakeVisible(timeLabel);
    timeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, TIME_ID, timeSlider);

    addAndMakeVisible(lfoFrequencySlider);
    lfoFrequencySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    lfoFrequencySlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    addAndMakeVisible(lfoFrequencyLabel);
    lfoFrequencyLabel.setText(LFO_FREQUENCY_NAME, dontSendNotification);
    lfoFrequencyLabel.setJustificationType(Justification::centred);
    lfoFrequencyLabel.attachToComponent(&lfoFrequencySlider, false);
    addAndMakeVisible(lfoFrequencyLabel);
    lfoFrequencyAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, LFO_FREQUENCY_ID, lfoFrequencySlider);

}

DaFlangeAudioProcessorEditor::~DaFlangeAudioProcessorEditor()
{
}

//==============================================================================
void DaFlangeAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);
}

void DaFlangeAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const int buttonSize = 80;
    Rectangle<int> area(10, 30, getWidth(), getHeight() - 60);
    timeSlider.setBounds(area.removeFromLeft(buttonSize));
    lfoFrequencySlider.setBounds(area.removeFromLeft(buttonSize));
}
