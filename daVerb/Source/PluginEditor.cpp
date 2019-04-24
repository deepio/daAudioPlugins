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
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (400, 300);
    const int sliderBoxWidth = 50;
    const int sliderBoxHeight= 20;
    
    addAndMakeVisible(roomSizeSlider);
    roomSizeSlider.setSliderStyle(Slider::RotaryHorizontalVerticalDrag);
    roomSizeSlider.setTextBoxStyle(Slider::TextBoxBelow, false, sliderBoxWidth, sliderBoxHeight);
    addAndMakeVisible(roomSizeLabel);
    roomSizeLabel.setText("Room Size", dontSendNotification);
    roomSizeLabel.setJustificationType(Justification::centred);
    roomSizeLabel.attachToComponent(&roomSizeSlider, false);
    roomSizeAttachment = std::make_unique<AudioProcessorValueTreeState::SliderAttachment>(processor.mParameterTree, ROOM_SIZE_ID, roomSizeSlider);
}

DaVerbAudioProcessorEditor::~DaVerbAudioProcessorEditor()
{
}

//==============================================================================
void DaVerbAudioProcessorEditor::paint (Graphics& g)
{
    // (Our component is opaque, so we must completely fill the background with a solid colour)
    g.fillAll (Colours::black);
}

void DaVerbAudioProcessorEditor::resized()
{
    // This is generally where you'll want to lay out the positions of any
    // subcomponents in your editor..
    const int buttonSize = 80;
    Rectangle<int> area(10, 30, getWidth(), getHeight() - 60);
    roomSizeSlider.setBounds(area.removeFromLeft(buttonSize));
}
