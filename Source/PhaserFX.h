/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    Phaser.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class PhaserFX
{
public:
    PhaserFX();
    ~PhaserFX();
    
    /** Prepares the phaser*/
    void prepare(const dsp::ProcessSpec& spec);
    
    /** Resets the phaser*/
    void reset();
    
    /** Returns true if the phaser is active*/
    bool isActive();

    /** Sets the phasers parameters*/
    void setParameters(float rate, float depth, float frequency, float feedback, float mix);
    
    /** Processes the AudioBuffer reference through the phaser*/
    void process(AudioBuffer<float>& bufferToProcess);
    
private:
    dsp::Phaser<float> phaser;
    
    float mix = 0;
};
