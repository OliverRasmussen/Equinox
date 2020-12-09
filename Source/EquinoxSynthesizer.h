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
#include "StateManager.h"

#define MAX_VOICES 16

class EquinoxSynthesizer : public juce::ValueTree::Listener
{
public:
    
    enum synthMode {oscSynthMode, sampleSynthMode};
    
    Synth oscillatorSynth;
    
    Synth sampleSynth;
    
    EquinoxSynthesizer();
    
    ~EquinoxSynthesizer();
    
    void initialize();
    
    static int getNumInstances();
    
    std::string instanceNumAsString() const;
    
    void valueTreeChildAdded (ValueTree &parentTree, ValueTree &childWhichHasBeenAdded) override;
    
    void valueTreePropertyChanged(ValueTree&, const Identifier&) override;
    
    void addParameters(std::vector<std::unique_ptr<RangedAudioParameter>>&);
    
    void setVoices();
    
    void loadAudioSample(AudioSample&);
    
    void setSynthMode(int);
    
    void switchVoicingMode(bool);
    
    void clearAllCurrentNotes();
    
    void prepareToPlay(double, int, int);
    
    void prepareVoices();
    
    void updateSynth();
    
    template<typename T>
    void setVoiceParameters(T);
    
    void renderNextBlock(AudioBuffer<float>&, MidiBuffer&);

private:
    
    bool isSynthActive() const;
    
    bool isMonophonic = false;
    
    double sampleRate;
    
    int samplesPerBlock;
    
    int numChannels;
    
    dsp::ProcessSpec spec;
    
    synthMode currentSynthMode;
    
    AudioFormatManager formatManager;
    
    static int objCounter;
    
    int instanceNum;
    
    int numVoices = 16;
};
