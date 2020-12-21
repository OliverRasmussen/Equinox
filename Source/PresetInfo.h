/*
  ==============================================================================

    PresetInfo.h
    Created: 21 Dec 2020 6:40:13pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
// Struct used for storing information about a preset
struct PresetInfo
{
    int index;
    String name;
    
    PresetInfo(int index, String name) : index(index), name(name)
    {
    }
};
