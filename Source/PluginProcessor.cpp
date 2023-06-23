/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AllPassFilterAudioProcessor::AllPassFilterAudioProcessor()
     : AudioProcessor (BusesProperties().withInput  ("Input",  juce::AudioChannelSet::stereo(), true)
                                        .withOutput ("Output", juce::AudioChannelSet::stereo(), true)),
                                        delayLineSize(0), delayIndex(0), delayLineGain(0.5), lastOutput(0.0)

{
    //delayLine.setSize(2, 0);
}

AllPassFilterAudioProcessor::~AllPassFilterAudioProcessor()
{
}

//==============================================================================
const juce::String AllPassFilterAudioProcessor::getName() const
{
    return "All Pass Filter";
}

bool AllPassFilterAudioProcessor::acceptsMidi() const
{
    return false;
}

bool AllPassFilterAudioProcessor::producesMidi() const
{
    return false;
}

bool AllPassFilterAudioProcessor::isMidiEffect() const
{
    return false;
}

double AllPassFilterAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int AllPassFilterAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int AllPassFilterAudioProcessor::getCurrentProgram()
{
    return 0;
}

void AllPassFilterAudioProcessor::setCurrentProgram (int index)
{
}

const juce::String AllPassFilterAudioProcessor::getProgramName (int index)
{
    return {};
}

void AllPassFilterAudioProcessor::changeProgramName (int index, const juce::String& newName)
{
}

//==============================================================================
void AllPassFilterAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    delayLineSize = sampleRate;
    setLatencySamples(delayLineSize);
    delayLine.setSize(2, delayLineSize);
    delayLine.clear();
    filterSampleRate = static_cast<float>(sampleRate);
}

void AllPassFilterAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}


bool AllPassFilterAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
    if (layouts.getMainInputChannelSet()  == juce::AudioChannelSet::disabled()
     || layouts.getMainOutputChannelSet() == juce::AudioChannelSet::disabled())
        return false;

    if (layouts.getMainOutputChannelSet() != juce::AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != juce::AudioChannelSet::stereo())
        return false;

    return layouts.getMainInputChannelSet() == layouts.getMainOutputChannelSet();
}


void AllPassFilterAudioProcessor::processBlock (juce::AudioBuffer<float>& buffer, juce::MidiBuffer& midiMessages)
{
//    const int numSamples = buffer.getNumSamples();
//    const float* inputChannelData = buffer.getReadPointer(0);
//    float* outputChannelData = buffer.getWritePointer(0);
//
//    for (int sample = 0; sample < numSamples; ++sample)
//    {
//        float inputSample = inputChannelData[sample];
//        float outputSample = processSample(inputSample);
//        outputChannelData[sample] = outputSample;s
//    }
//
    
    const int totalNumInputChannels = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

    for (int channel = 0; channel < totalNumInputChannels; ++channel)
    {
        auto* inputChannelData = buffer.getReadPointer(channel);
        auto* outputChannelData = buffer.getWritePointer(channel);

        for (int sample = 0; sample < buffer.getNumSamples(); ++sample)
        {
            float input = inputChannelData[sample];
            float output = processSample(input, channel);
            outputChannelData[sample] = output;
        }
    }

    // If the number of output channels is greater than the number of input channels,
    // copy the input channels to the remaining output channels.
    for (int channel = totalNumInputChannels; channel < totalNumOutputChannels; ++channel)
    {
        buffer.copyFrom(channel, 0, buffer, 0, 0, buffer.getNumSamples());
    }
}

//==============================================================================
bool AllPassFilterAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

juce::AudioProcessorEditor* AllPassFilterAudioProcessor::createEditor()
{
    return new AllPassFilterAudioProcessorEditor (*this);
}

//==============================================================================
void AllPassFilterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.
}

void AllPassFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.
}

void AllPassFilterAudioProcessor::setSize(int size)
{
    delayLineSize = size;
}

void AllPassFilterAudioProcessor::setGain(float newGain)
{
    delayLineGain = newGain;
}

//==============================================================================

float AllPassFilterAudioProcessor::processSample(float input, int channel)
{
    float delaySample = delayLine.getSample(channel, delayIndex);
    float output = -input + delaySample;
    delayLine.setSample(channel, delayIndex, input + (delaySample * delayLineGain));
    delayIndex = (delayIndex + 1) % delayLineSize;
    lastOutput = output;
    return output;
}

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AllPassFilterAudioProcessor();
}


