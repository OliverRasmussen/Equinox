/*
  ==============================================================================

    AmpEnvelope.h
    Created: 18 Apr 2020 3:31:42am
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "ADSREnvelope.h"

class AmpEnvelope : public ADSREnvelope
{
public:

    void prepareToPlay(double sampleRate) override;
           
    void setEnvelope(float *attack, float *decay, float *sustain, float *release) override;
           
    float getNextSample();
    
    void setSampleRate(double sampleRate);
           
    void noteOn() override;
           
    void noteOff() override;
           
    bool isActive() const override;
    
    void setParameters() override;
    
private:
    
    ADSR envelope;
    
    ADSR::Parameters envelopeParameters;
};

