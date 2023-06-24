/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AllPassFilterAudioProcessorEditor::AllPassFilterAudioProcessorEditor (AllPassFilterAudioProcessor& p)
    : AudioProcessorEditor (&p), audioProcessor (p)
{
    // Make sure that before the constructor has finished, you've set the
    // editor's size to whatever you need it to be.
    setSize (260, 400);
    
    delayLineSizeSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    delayLineSizeSlider.setRange (1.0, 1000.0, 1.0);
    delayLineSizeSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    delayLineSizeSlider.setPopupDisplayEnabled (true, false, this);
    delayLineSizeSlider.setTextValueSuffix (" ms");
    delayLineSizeSlider.setSkewFactorFromMidPoint (200.0);
    delayLineSizeSlider.setValue(1000.0);
 
    // this function adds the slider to the editor
    addAndMakeVisible (&delayLineSizeSlider);
    delayLineSizeSlider.addListener (this);
    
    addAndMakeVisible (delayLineSizeLabel);
    delayLineSizeLabel.setText ("Delay", juce::dontSendNotification);
    delayLineSizeLabel.attachToComponent (&delayLineSizeSlider, true);
    
    delayLineGainSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    delayLineGainSlider.setRange (0.0, 100.0, 1.0);
    delayLineGainSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    delayLineGainSlider.setPopupDisplayEnabled (true, false, this);
    delayLineGainSlider.setTextValueSuffix (" %");
    delayLineGainSlider.setValue(50.0);

    // this function adds the slider to the editor
    addAndMakeVisible (&delayLineGainSlider);
    delayLineGainSlider.addListener (this);
    
    addAndMakeVisible (delayLineGainLabel);
    delayLineGainLabel.setText ("Gain", juce::dontSendNotification);
    delayLineGainLabel.attachToComponent (&delayLineGainSlider, true);
}

AllPassFilterAudioProcessorEditor::~AllPassFilterAudioProcessorEditor()
{
}

//==============================================================================
void AllPassFilterAudioProcessorEditor::paint (juce::Graphics& g)
{
    g.fillAll (juce::Colours::white);

    g.setColour (juce::Colours::black);
    g.setFont (15.0f);
    
    delayLineSizeSlider.setBounds (40, 30, 20, getHeight() - 60);
    delayLineGainSlider.setBounds (200, 30, 20, getHeight() - 60);
    
    g.drawFittedText ("Delay Line Size", 10, 0, getWidth(), 30, juce::Justification::left, 1);
    g.drawFittedText ("Delay Line Gain", -10, 0, getWidth(), 30, juce::Justification::right, 1);
}

void AllPassFilterAudioProcessorEditor::resized()
{
}

void AllPassFilterAudioProcessorEditor::sliderValueChanged (juce::Slider* slider)
{
    if (slider == &delayLineSizeSlider){
        audioProcessor.delayLineSize = delayLineSizeSlider.getValue() * audioProcessor.getSampleRate() / 1000;
    }
    else if(slider == &delayLineGainSlider){
        audioProcessor.delayLineGain = delayLineGainSlider.getValue() / 100;
    }
    
}
