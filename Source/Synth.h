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
class Synth : public Synthesiser
{
public:
    Synth();
    ~Synth();
    
protected:
    SynthesiserVoice* findFreeVoice (SynthesiserSound* soundToPlay, int midiChannel, int midiNoteNumber, const bool stealIfNoneAvailable) const override;
    
    void noteOn (const int midiChannel, const int midiNoteNumber, const float velocity) override;
    
    void handleMidiEvent(const MidiMessage &) override;
    
    Array<MidiMessage> notesHeldDown;
    
 private:
    bool monoEnabled() const;
};
