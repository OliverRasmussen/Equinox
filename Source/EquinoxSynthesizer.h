/*
  ==============================================================================
       ______ ____   __  __ ____ _   __ ____  _  __
      / ____// __ \ / / / //  _// | / // __ \| |/ /
     / __/  / / / // / / / / / /  |/ // / / /|   /
    / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
   /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
                                                
   EquinoxSynthesizer.h
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

class EquinoxSynthesizer : public ValueTree::Listener
{
public:
    
    enum synthMode {oscSynthMode, sampleSynthMode};
    
    Synth oscillatorSynth;
    
    Synth sampleSynth;
    
    EquinoxSynthesizer(StateManager&, int);
    
    ~EquinoxSynthesizer();
    
    /**Initializes the synthesizer*/
    void initialize();
    
    /** Returns this instance number as a string*/
    std::string instanceNumAsString() const;
    
    /** Adds the synthesizers parameters to a passed in vector*/
    void addParameters(std::vector<std::unique_ptr<RangedAudioParameter>>&);
    
    /** Initializes the voices*/
    void setVoices();
    
    /** loads an AudioSample*/
    void loadAudioSample(AudioSample&);
    
    /** Sets the synthesizers mode to either oscSynthMode or sampleSynthMode*/
    void setSynthMode(int);
    
    /** Used for switching the voicing mode*/
    void switchVoicingMode(bool);
    
    /** Clears all current notes*/
    void clearAllCurrentNotes();
    
    /** Prepares the synthesizer */
    void prepareToPlay(double, int, int);
    
    /** Prepares the voices*/
    void prepareVoices();
    
    /** Updates the synthesizer and its voices*/
    void update();
    
    /** Used for setting the voices parameters*/
    template<typename T>
    void setVoiceParameters(T);
    
    /** Renders the next block*/
    void renderNextBlock(AudioBuffer<float>&, MidiBuffer&);

private:
    /** Receives a callback whenever a ValueTree child is added*/
    void valueTreeChildAdded (ValueTree&, ValueTree&) override;
    
    /** Receives a callback whenever a property in the ValueTree has changed*/
    void valueTreePropertyChanged(ValueTree&, const Identifier&) override;
    
    /** Returns true if the synth is currently active*/
    bool isSynthActive() const;

    StateManager& stateManager;
    
    bool isMonophonic = false;
    
    double sampleRate = 44100;
    
    int samplesPerBlock = 512;
    
    int numChannels = 2;
    
    dsp::ProcessSpec spec;
    
    synthMode currentSynthMode;
    
    AudioFormatManager formatManager;
    
    int instanceNum;
    
    int numVoices = 16;
    
    bool needsReset = false;
    
    bool needsUpdate = false;
    
    bool loadNewAudioSample = false;
};
