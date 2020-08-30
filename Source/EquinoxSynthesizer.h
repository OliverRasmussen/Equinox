/*
  ==============================================================================

    EquinoxSynthesizer.h
    Created: 8 Apr 2020 9:27:00pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "Synth.h"
#include "OscSynthVoice.h"
#include "SampleSynthVoice.h"

class EquinoxSynthesizer
{
public:
    
    enum synthMode {oscSynthMode, sampleSynthMode};
    
    enum voicingMode {polyphonicMode, monophonicMode};
    
    Synth oscillatorSynth;
    
    Synth sampleSynth;
    
    EquinoxSynthesizer(AudioProcessorValueTreeState&);
    
    ~EquinoxSynthesizer();
    
    static int getNumInstances();
    
    std::string instanceNumAsStr() const;
    
//    template<typename ParameterType, typename ValueType>
//    std::unique_ptr<ParameterType> createSynthParameter(std::string& paramId, std::string& paramName, bool parameterIsBool, ValueType defaultValue, ValueType minValue = 0, ValueType maxValue = 0, ValueType intervalValue = 0, ValueType skewFactor = 0, bool useSymmetricSkew = false);
    
    void addParameters(std::vector<std::unique_ptr<RangedAudioParameter>>&);
    
    void setVoices(int newNumberOfVoices = 16);
    
    void loadNewSample();
    
    void setSynthMode(int newSynthMode);
    
    void switchVoicingMode(bool enableMono);
    
    void clearAllCurrentNotes();
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    
    void prepareVoices();
    
    void update();
    
    template<typename T>
    void setVoiceParameters(T voice);
    
    void renderNextBlock(AudioBuffer<float>&, MidiBuffer&);

private:
    
    double sampleRate;
    int samplesPerBlock;
    int numChannels;
    dsp::ProcessSpec spec;
    
    synthMode currentSynthMode;
    
    voicingMode currentVoicingMode;
    
    AudioFormatManager formatManager;
    AudioFormatReader* formatReader {nullptr};
    
    static int objCounter;
    
    int instanceNum;
    
    int numVoices = 16;
    
    OscSynthVoice* oscVoice;
    
    SampleSynthVoice* sampleVoice;
    
    AudioProcessorValueTreeState& treeState;
    
    
};
