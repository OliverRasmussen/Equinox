/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    Synth.h
    Author:  Oliver Rasmussen
  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "OscSynthVoice.h"
#include "SampleSynthVoice.h"
class Synth : public Synthesiser
{
public:
    
    enum voiceType {oscillator, sampler};
    
    Synth(voiceType synthVoiceType);
    
    ~Synth();
    
    void prepare(dsp::ProcessSpec& spec);
    
    void addVoices(int voicesToAdd);
    
    void clearAllCurrentNotes();
    
protected:
    /** Method for finding a free voice*/
    SynthesiserVoice* findFreeVoice (SynthesiserSound* soundToPlay, int midiChannel, int midiNoteNumber, const bool stealIfNoneAvailable) const override;
    
    /** Method that gets called when a midi note is triggered*/
    void noteOn (const int midiChannel, const int midiNoteNumber, const float velocity) override;
    
    /** Method that gets called when a midi note is released*/
    void noteOff (const int midiChannel, const int midiNoteNumber, const float velocity, const bool allowTailOff) override;
    
    /** Method used for handling midi events*/
    void handleMidiEvent(const MidiMessage &) override;
    
    Array<MidiMessage> notesHeldDown;
    
 private:
    /** Returns true if the synth currently only has one voice*/
    bool monoEnabled() const;
    
    voiceType _voiceType;
};
