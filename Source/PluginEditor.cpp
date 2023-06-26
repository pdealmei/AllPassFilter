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
    setSize (260, 400);
    
    delayLineSizeSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    delayLineSizeSlider.setRange (1.0, 1000.0, 1.0);
    delayLineSizeSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    delayLineSizeSlider.setPopupDisplayEnabled (true, false, this);
    delayLineSizeSlider.setTextValueSuffix (" ms");
    delayLineSizeSlider.setSkewFactorFromMidPoint (200.0);
    
    delayLineSizeAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "size", delayLineSizeSlider);

 
    addAndMakeVisible (&delayLineSizeSlider);
    
    addAndMakeVisible (delayLineSizeLabel);
    delayLineSizeLabel.setText ("Delay", juce::dontSendNotification);
    delayLineSizeLabel.attachToComponent (&delayLineSizeSlider, true);
    
    delayLineGainSlider.setSliderStyle (juce::Slider::LinearBarVertical);
    delayLineGainSlider.setRange (0.0, 100.0, 1.0);
    delayLineGainSlider.setTextBoxStyle (juce::Slider::NoTextBox, false, 90, 0);
    delayLineGainSlider.setPopupDisplayEnabled (true, false, this);
    delayLineGainSlider.setTextValueSuffix (" %");
    
    delayLineGainAttachment = std::make_unique<juce::AudioProcessorValueTreeState::SliderAttachment>(audioProcessor.apvts, "gain", delayLineGainSlider);
    
    addAndMakeVisible (&delayLineGainSlider);
    
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


