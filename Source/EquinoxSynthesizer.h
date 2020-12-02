/*
  ==============================================================================
       ______ ____   __  __ ____ _   __ ____  _  __
      / ____// __ \ / / / //  _// | / // __ \| |/ /
     / __/  / / / // / / / / / /  |/ // / / /|   /
    / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
   /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
                                                
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

#define MAX_VOICES 16

class EquinoxSynthesizer
{
public:
    
    enum synthMode {oscSynthMode, sampleSynthMode};
    
    Synth oscillatorSynth;
    
    Synth sampleSynth;
    
    EquinoxSynthesizer(AudioProcessorValueTreeState&);
    
    ~EquinoxSynthesizer();
    
    static int getNumInstances();
    
    std::string instanceNumAsString() const;
    
    void addParameters(std::vector<std::unique_ptr<RangedAudioParameter>>&);
    
    void setVoices();
    
    void loadSampleFromFile(File sampleFile, String sampleName);
    
    void setSynthMode(int newSynthMode);
    
    void switchVoicingMode(bool enableMono);
    
    void clearAllCurrentNotes();
    
    void prepareToPlay(double sampleRate, int samplesPerBlock, int numChannels);
    
    void prepareVoices();
    
    void updateSynth();
    
    template<typename T>
    void setVoiceParameters(T voice);
    
    void renderNextBlock(AudioBuffer<float>&, MidiBuffer&);

private:
    
    bool isSynthActive() const;
    
    bool isMonophonic = false;
    
    bool notesPlaying = false;
    
    double sampleRate;
    
    int samplesPerBlock;
    
    int numChannels;
    
    dsp::ProcessSpec spec;
    
    synthMode currentSynthMode;
    
    AudioFormatManager formatManager;
    
    static int objCounter;
    
    int instanceNum;
    
    int numVoices = 16;
    
    OscSynthVoice* oscVoice;
    
    SampleSynthVoice* sampleVoice;
    
    AudioProcessorValueTreeState& treeState;
    
    
};
