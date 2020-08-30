/*
  ==============================================================================

    OscSynthSound.h
    Created: 4 Apr 2020 5:13:15pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once

#include <JuceHeader.h>

class OscSynthSound : public SynthesiserSound
{
public:
    
    bool appliesToNote (int midiNote) override;
    
    bool appliesToChannel (int midiChannel) override;
};
