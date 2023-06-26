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
class AllPassFilterAudioProcessorEditor  : public juce::AudioProcessorEditor
{
public:
    AllPassFilterAudioProcessorEditor (AllPassFilterAudioProcessor&);
    ~AllPassFilterAudioProcessorEditor() override;

    //==============================================================================
    void paint (juce::Graphics&) override;
    void resized() override;

private:
    AllPassFilterAudioProcessor& audioProcessor;
    juce::Slider delayLineSizeSlider;
    juce::Label delayLineSizeLabel;
    juce::Slider delayLineGainSlider;
    juce::Label delayLineGainLabel;
    
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayLineSizeAttachment;
    std::unique_ptr<juce::AudioProcessorValueTreeState::SliderAttachment> delayLineGainAttachment;
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (AllPassFilterAudioProcessorEditor)
};
