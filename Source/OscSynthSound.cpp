/*
  ==============================================================================

    OscSynthSound.cpp
    Created: 4 Apr 2020 5:13:15pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "OscSynthSound.h"

bool OscSynthSound::appliesToNote (int midiNote)
{
    return true;
}

bool OscSynthSound::appliesToChannel (int midiChannel)
{
    return true;
}
