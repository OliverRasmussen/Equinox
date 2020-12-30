/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    ADSREnvelope.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
class ADSREnvelope
{
public:
        
    virtual ~ADSREnvelope() {}
        
    virtual void prepareToPlay(double sampleRate) = 0;
        
    virtual void setEnvelope(float *attack, float *decay, float *sustain, float *release) = 0;
        
    virtual void noteOn() = 0;
        
    virtual void noteOff() = 0;
        
    virtual bool isActive() const = 0;
    
};
