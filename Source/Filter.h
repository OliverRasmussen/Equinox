/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    Filter.h
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
