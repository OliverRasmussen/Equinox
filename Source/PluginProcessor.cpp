/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

//==============================================================================
EquinoxAudioProcessor::EquinoxAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       ), synthLayer1(stateManager, 1),
                          synthLayer2(stateManager, 2),
                          synthLayer3(stateManager, 3),
                          masterEffectChain(stateManager),
                          stateManager(new AudioProcessorValueTreeState(*this, nullptr, "parameterstate", CreateParameterLayout()),
                          new AudioSampleValueTreeState("audiosamplestate"))
#endif
{
    synthLayer1.initialize();
    synthLayer2.initialize();
    synthLayer3.initialize();
    masterEffectChain.initialize();
}

EquinoxAudioProcessor::~EquinoxAudioProcessor()
{
}

//==============================================================================
const String EquinoxAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool EquinoxAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool EquinoxAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

bool EquinoxAudioProcessor::isMidiEffect() const
{
   #if JucePlugin_IsMidiEffect
    return true;
   #else
    return false;
   #endif
}

double EquinoxAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int EquinoxAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int EquinoxAudioProcessor::getCurrentProgram()
{
    return 0;
}

void EquinoxAudioProcessor::setCurrentProgram (int index)
{
}

const String EquinoxAudioProcessor::getProgramName (int index)
{
    return {};
}

void EquinoxAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void EquinoxAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
    
    ignoreUnused(samplesPerBlock);
    lastSampleRate = sampleRate;
    
    synthLayer1.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    synthLayer2.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    synthLayer3.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    
    masterEffectChain.reset();
    masterEffectChain.prepareToPlay(sampleRate, samplesPerBlock, getTotalNumOutputChannels());
    
}

void EquinoxAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool EquinoxAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void EquinoxAudioProcessor::processBlock (AudioBuffer<float>& buffer, MidiBuffer& midiMessages)
{
    ScopedNoDenormals noDenormals;
    
    auto totalNumInputChannels  = getTotalNumInputChannels();
    auto totalNumOutputChannels = getTotalNumOutputChannels();

    for (auto i = totalNumInputChannels; i < totalNumOutputChannels; ++i)
        buffer.clear (i, 0, buffer.getNumSamples());


    // Rendering the synthesizers
    synthLayer1.renderNextBlock(buffer, midiMessages);
    synthLayer2.renderNextBlock(buffer, midiMessages);
    synthLayer3.renderNextBlock(buffer, midiMessages);
    
    
    // Getting the currentPositionInfo
    getPlayHead()->getCurrentPosition(currentPositionInfo);
    
    // Processing the buffer through the effect chain
    masterEffectChain.process(buffer, currentPositionInfo.bpm);
}

//==============================================================================
bool EquinoxAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}

AudioProcessorEditor* EquinoxAudioProcessor::createEditor()
{
    return new EquinoxAudioProcessorEditor (*this);
}

//==============================================================================
void EquinoxAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    stateManager.saveStateToBinary(destData);
}

void EquinoxAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    stateManager.loadStateFromBinary(data, sizeInBytes);
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new EquinoxAudioProcessor();
}

AudioProcessorValueTreeState::ParameterLayout EquinoxAudioProcessor::CreateParameterLayout()
{
    std::vector<std::unique_ptr<RangedAudioParameter>> parameters;
    
    synthLayer1.addParameters(parameters);
    synthLayer2.addParameters(parameters);
    synthLayer3.addParameters(parameters);
    
    masterEffectChain.addParameters(parameters);
    
    
    return { parameters.begin(), parameters.end()};
    
}
