/*
  ==============================================================================

    Synth.h
    Created: 15 May 2020 8:12:53pm
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
