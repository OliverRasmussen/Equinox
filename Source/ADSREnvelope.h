/*
  ==============================================================================

    ADSREnvelope.h
    Created: 18 Apr 2020 3:31:26am
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
    
    virtual void setParameters() = 0;
    
};
