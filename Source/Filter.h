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
    /** Prepares the filter*/
    void prepareToPlay(dsp::ProcessSpec&);
    
    /** Resets the filter*/
    void reset();
    
    /** Sets the mode of the filter*/
    void setMode(float* mode);
    
    /** Returns true if the filter is active*/
    bool isActive() const;
    
    /** Sets the filters parameters*/
    void setFilter(float* cutoff, float* resonance, float* drive);
    
    /** Modulate the cutoff frequency*/
    void modulateCutoff(float cutoff);
    
    /** Returns the filters cutoff value*/
    float getCutoffValue() const;
    
    /** Processes an AudioBuffer through the filter*/
    void process(AudioBuffer<float>&);
    
private:
    dsp::LadderFilter<float> ladderFilter;
    float currentCutoffValue;
    float currentDriveValue;
    float currentResonanceValue;
    int filterMode = 0;
    int sampleRate;
};
