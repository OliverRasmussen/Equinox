/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>
#include "EquinoxSynthesizer.h"
#include "MasterEffectChain.h"
#include "StateManager.h"
#include "PresetManager.h"

//==============================================================================
/**
*/
class EquinoxAudioProcessor  : public AudioProcessor
{
public:
    //==============================================================================
    EquinoxAudioProcessor();
    ~EquinoxAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioBuffer<float>&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    bool isMidiEffect() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;
    
    EquinoxSynthesizer synthLayer1, synthLayer2, synthLayer3;
    
    MasterEffectChain masterEffectChain;
    
    StateManager stateManager;
    
    PresetManager presetManager;
    
    MidiKeyboardState midiKeyboardState;
private:
    AudioPlayHead::CurrentPositionInfo currentPositionInfo;
    
    AudioProcessorValueTreeState::ParameterLayout CreateParameterLayout();
    
    double lastSampleRate;
    double currentBPM = 120;
    
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (EquinoxAudioProcessor)
};
