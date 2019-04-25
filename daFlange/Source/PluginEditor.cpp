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
    setSize(640, 399);

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

    addAndMakeVisible(intensitySlider);
    intensitySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    intensitySlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    addAndMakeVisible(intensityLabel);
    intensityLabel.setText(INTENSITY_NAME, dontSendNotification);
    intensityLabel.setJustificationType(Justification::centred);
    intensityLabel.attachToComponent(&intensitySlider, false);
    intensityAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, INTENSITY_ID, intensitySlider);

    addAndMakeVisible(wetDrySlider);
    wetDrySlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    wetDrySlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    addAndMakeVisible(wetDryLabel);
    wetDryLabel.setText(WET_DRY_NAME, dontSendNotification);
    wetDryLabel.setJustificationType(Justification::centred);
    wetDryLabel.attachToComponent(&wetDrySlider, false);
    wetDryAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, WET_DRY_ID, wetDrySlider);
}

DaFlangeAudioProcessorEditor::~DaFlangeAudioProcessorEditor()
{
}

//==============================================================================
void DaFlangeAudioProcessorEditor::paint (Graphics& g)
{
    Image background = ImageCache::getFromMemory(BinaryData::bg2_jpg, BinaryData::bg2_jpgSize);
    g.drawImageAt(background, 0, 0);
}

void DaFlangeAudioProcessorEditor::resized()
{
    const int buttonSize = 110;
    Rectangle<int> area(180, 210, getWidth(), getHeight() - 240);
    feedbackSlider.setBounds(area.removeFromLeft(buttonSize));
    widthSlider.setBounds(area.removeFromLeft(buttonSize));
    intensitySlider.setBounds(area.removeFromLeft(buttonSize));
    wetDrySlider.setBounds(area.removeFromLeft(buttonSize));
}
