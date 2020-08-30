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
    void handleMidiEvent(const MidiMessage &) override;
    
    Array<MidiMessage> notesHeldDown;
};
