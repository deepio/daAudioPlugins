/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
DaVerbAudioProcessorEditor::DaVerbAudioProcessorEditor (DaVerbAudioProcessor& p)
    : AudioProcessorEditor (&p), processor (p)
{
    setSize(640, 426);
    const int sliderBoxWidth = 50;
    const int sliderBoxHeight= 20;

    addAndMakeVisible(roomSizeSlider);
    roomSizeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    roomSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    roomSizeSlider.setColour(Slider::textBoxOutlineColourId, Colours::black);
    addAndMakeVisible(roomSizeLabel);
    roomSizeLabel.setText(ROOM_SIZE_NAME, dontSendNotification);
    roomSizeLabel.setColour(Label::textColourId, Colours::black);
    roomSizeLabel.setJustificationType(Justification::centred);
    roomSizeLabel.attachToComponent(&roomSizeSlider, false);
    roomSizeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, ROOM_SIZE_ID, roomSizeSlider);

    addAndMakeVisible(dampingSlider);
    dampingSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dampingSlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    dampingSlider.setColour(Slider::textBoxOutlineColourId, Colours::black);
    addAndMakeVisible(dampingLabel);
    dampingLabel.setText(DAMPING_NAME, dontSendNotification);
    dampingLabel.setColour(Label::textColourId, Colours::black);
    dampingLabel.setJustificationType(Justification::centred);
    dampingLabel.attachToComponent(&dampingSlider, false);
    dampingAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, DAMPING_ID, dampingSlider);

    addAndMakeVisible(widthSlider);
    widthSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    widthSlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    widthSlider.setColour(Slider::textBoxOutlineColourId, Colours::black);
    addAndMakeVisible(widthLabel);
    widthLabel.setText(WIDTH_NAME, dontSendNotification);
    widthLabel.setColour(Label::textColourId, Colours::black);
    widthLabel.setJustificationType(Justification::centred);
    widthLabel.attachToComponent(&widthSlider, false);
    widthAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, WIDTH_ID, widthSlider);

    addAndMakeVisible(wetLevelSlider);
    wetLevelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    wetLevelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    wetLevelSlider.setColour(Slider::textBoxOutlineColourId, Colours::black);
    addAndMakeVisible(wetLevelLabel);
    wetLevelLabel.setText(WET_LEVEL_NAME, dontSendNotification);
    wetLevelLabel.setColour(Label::textColourId, Colours::black);
    wetLevelLabel.setJustificationType(Justification::centred);
    wetLevelLabel.attachToComponent(&wetLevelSlider, false);
    wetLevelAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, WET_LEVEL_ID, wetLevelSlider);

    addAndMakeVisible(dryLevelSlider);
    dryLevelSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    dryLevelSlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    dryLevelSlider.setColour(Slider::textBoxOutlineColourId, Colours::black);
    addAndMakeVisible(dryLevelLabel);
    dryLevelLabel.setText(DRY_LEVEL_NAME, dontSendNotification);
    dryLevelLabel.setColour(Label::textColourId, Colours::black);
    dryLevelLabel.setJustificationType(Justification::centred);
    dryLevelLabel.attachToComponent(&dryLevelSlider, false);
    dryLevelAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, DRY_LEVEL_ID, dryLevelSlider);

    getLookAndFeel().setColour(Slider::thumbColourId, Colours::white);
}

DaVerbAudioProcessorEditor::~DaVerbAudioProcessorEditor()
{
}

//==============================================================================
void DaVerbAudioProcessorEditor::paint (Graphics& g)
{
    Image background = ImageCache::getFromMemory(BinaryData::bg_jpg, BinaryData::bg_jpgSize);
    g.drawImageAt(background, 0, 0);
}

void DaVerbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const int buttonSize = 80;
    Rectangle<int> area(10, 30, getWidth(), getHeight() - 290);
    roomSizeSlider.setBounds(area.removeFromLeft(buttonSize));
    dampingSlider.setBounds(area.removeFromLeft(buttonSize));
    widthSlider.setBounds(area.removeFromLeft(buttonSize));
    wetLevelSlider.setBounds(area.removeFromLeft(buttonSize));
    dryLevelSlider.setBounds(area.removeFromLeft(buttonSize));
}
