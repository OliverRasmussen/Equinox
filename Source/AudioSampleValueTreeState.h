/*
  ==============================================================================

    AudioSampleValueTreeState.h
    Created: 8 Dec 2020 3:42:03pm
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
    
    void addAudioSample(File audioFile, String sampleId);
    
    std::unique_ptr<AudioSample> getAudioSample(String sampleId);
    
    void replaceState(ValueTree newState);
    
    ValueTree state;
    
    AudioFormatManager formatManager;
    
private:
    
    CriticalSection replacingState;
    
};
