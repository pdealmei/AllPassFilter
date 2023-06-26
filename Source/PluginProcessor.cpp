/*
  ==============================================================================

    This file contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
AllPassFilterAudioProcessor::AllPassFilterAudioProcessor()
     : AudioProcessor (BusesProperties().withInput  ("Input",  juce::AudioChannelSet::mono(), true)
                                        .withOutput ("Output", juce::AudioChannelSet::mono(), true)),
        apvts(*this, nullptr, "Parameters", createParameters()),delayIndex(0)

{
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
    return 1;
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
    delayLine.setSize(getTotalNumOutputChannels(), sampleRate);
    delayLine.clear();
}

void AllPassFilterAudioProcessor::releaseResources()
{
    delayLine.clear();
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
    const int numSamples = buffer.getNumSamples();
    const float* inputChannelData = buffer.getReadPointer(0);
    float* outputChannelData = buffer.getWritePointer(0);

    for (int sample = 0; sample < numSamples; ++sample)
    {
        float inputSample = inputChannelData[sample];
        float outputSample = processSample(inputSample,0);
        outputChannelData[sample] = outputSample;
    }
}

//==============================================================================
bool AllPassFilterAudioProcessor::hasEditor() const
{
    return true;
}

juce::AudioProcessorEditor* AllPassFilterAudioProcessor::createEditor()
{
    return new AllPassFilterAudioProcessorEditor (*this);
}

//==============================================================================
void AllPassFilterAudioProcessor::getStateInformation (juce::MemoryBlock& destData)
{
//    juce::MemoryOutputStream (destData, true).writeFloat (*delayLineSize);
//    juce::MemoryOutputStream (destData, true).writeFloat (*delayLineGain);
    
//    std::unique_ptr<juce::XmlElement> xml (new juce::XmlElement ("AllPassParameters"));
//    xml->setAttribute ("size", (double) *delayLineSize);
//    xml->setAttribute ("gain", (double) *delayLineGain);
//    copyXmlToBinary (*xml, destData);
}

void AllPassFilterAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
//    *delayLineSize = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
//    *delayLineGain = juce::MemoryInputStream (data, static_cast<size_t> (sizeInBytes), false).readFloat();
    
//    std::unique_ptr<juce::XmlElement> xmlState (getXmlFromBinary (data, sizeInBytes));
//
//    if (xmlState.get() != nullptr)
//    {
//        if (xmlState->hasTagName ("AllPassParameters"))
//        {
//            *delayLineSize = (float) xmlState->getDoubleAttribute ("size", 33.0);
//            *delayLineGain = (float) xmlState->getDoubleAttribute ("gain", 0.5);
//        }
//    }
}

//==============================================================================

float AllPassFilterAudioProcessor::processSample(float input, int channel)
{
    float delaySample = delayLine.getSample(channel, delayIndex);
    float output = -input + delaySample;
    delayLine.setSample(channel, delayIndex, input + (delaySample * apvts.getRawParameterValue("size")->load()));
    delayIndex = (delayIndex + 1) % (int) (apvts.getRawParameterValue("gain")->load() * this->getSampleRate() / 1000);
    return output;
}

// This creates new instances of the plugin..
juce::AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new AllPassFilterAudioProcessor();
}

juce::AudioProcessorValueTreeState::ParameterLayout AllPassFilterAudioProcessor::createParameters(){
    std::vector<std::unique_ptr<juce::RangedAudioParameter>> params;
    params.push_back(std::make_unique<juce::AudioParameterFloat>("size","delayLineSize", 1.0f,1000.0f,33.0f));
    params.push_back(std::make_unique<juce::AudioParameterFloat>("gain","delayLineGain", 0.0f,1.0f,0.5f));
    
    return {params.begin(),params.end()};
}

