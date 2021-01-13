/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    AudioSampleValueTreeState.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "AudioSample.h"

class AudioSampleValueTreeState
{
public:
    
    AudioSampleValueTreeState(const Identifier &type);
    
    ~AudioSampleValueTreeState();
    
    /** Adds a file as an AudioSample to the AudioSampleValueTreeState*/
    void addAudioSample(File audioFile, String sampleId);
    
    /** Returns a pointer to a specific sample*/
    std::unique_ptr<AudioSample> getAudioSample(String sampleId);
    
    /** Replaces the AudioSampleValueTreeStates internal ValueTree*/
    void replaceState(ValueTree newState);
    
    ValueTree state;
    
    AudioFormatManager formatManager;
    
private:
    
    CriticalSection replacingState;
    
};
