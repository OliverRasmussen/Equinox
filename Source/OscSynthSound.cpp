/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    OscSynthSound.cpp
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
