/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin editor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "PluginProcessor.h"

//==============================================================================
/**
*/
class AllPassFilterAudioProcessorEditor  : public juce::AudioProcessorEditor,private juce::Slider::Listener
{
public:
    AllPassFilterAudioProcessorEditor (AllPassFilterAudioProcessor&);
    ~AllPassFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    // This reference is provided as a quick way for your editor to
    // access the processor object that created it.
    AllPassFilterAudioProcessor& audioProcessor;
    juce::Slider delayLineSizeSlider;
    juce::Label delayLineSizeLabel;
    juce::Slider delayLineGainSlider;
    juce::Label delayLineGainLabel;
    void sliderValueChanged (juce::Slider* slider) override;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AllPassFilterAudioProcessorEditor)
};
