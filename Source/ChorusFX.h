/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    Chorus.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class ChorusFX
{
public:
    ChorusFX();
    ~ChorusFX();
    
    void prepare(const dsp::ProcessSpec& spec);
    
    void reset();
    
    bool isActive();

    void setParameters(float rate, float depth, float delay, float feedback, float mix);
    
    void process(AudioBuffer<float>& bufferToProcess);
    
private:
    dsp::Chorus<float> chorus;
    
    float mix = 0;
};
