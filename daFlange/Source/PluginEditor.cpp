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


    addAndMakeVisible(feedbackSlider);
    feedbackSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    feedbackSlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    addAndMakeVisible(feedbackLabel);
    feedbackLabel.setText(FEEDBACK_NAME, dontSendNotification);
    feedbackLabel.setJustificationType(Justification::centred);
    feedbackLabel.attachToComponent(&feedbackSlider, false);
    feedbackAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, FEEDBACK_ID, feedbackSlider);

    addAndMakeVisible(widthSlider);
    widthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    addAndMakeVisible(widthLabel);
    widthLabel.setText(WIDTH_NAME, dontSendNotification);
    widthLabel.setJustificationType(Justification::centred);
    widthLabel.attachToComponent(&widthSlider, false);
    widthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, WIDTH_ID, widthSlider);

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
    const int buttonSize = 80;
    Rectangle<int> area(10, 30, getWidth(), getHeight() - 60);
    feedbackSlider.setBounds(area.removeFromLeft(buttonSize));
    widthSlider.setBounds(area.removeFromLeft(buttonSize));
}
