/*
  ==============================================================================

    Filter.h
    Created: 15 Apr 2020 9:44:46pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>

class Filter
{
public:

    void prepareToPlay(dsp::ProcessSpec&);
    
    void reset();
    
    void setMode(float* mode);
    
    bool isActive();
    
    void setFilter(float* cutoff, float* resonance, float* drive);
    
    void setCutoff(float cutoff);
    
    float getCutoffValue() const;
    
    void process(AudioBuffer<float>&);
    
private:
    dsp::LadderFilter<float> ladderFilter;
    float currentCutoffValue;
    int filterMode = 0;
    int sampleRate;
};
