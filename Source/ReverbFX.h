/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    Reverb.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class ReverbFX
{
public:
    ReverbFX();
    ~ReverbFX();
    
    /** Prepares the reverb*/
    void prepare(const dsp::ProcessSpec& spec);
    
    /** Resets the reverb*/
    void reset();
    
    /** Returns true if the reverb is active*/
    bool isActive();

    /** Sets the reverbs parameters*/
    void setParameters(float roomSize, float damping, float width, float mix);
    
    /** Processes the AudioBuffer reference through the reverb*/
    void process(AudioBuffer<float>& bufferToProcess);
    
private:
    dsp::Reverb::Parameters reverbParameters;
    dsp::Reverb reverb;
};
