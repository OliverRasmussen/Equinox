/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    AmpEnvelope.h
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
    
private:
    
    ADSR envelope;
    
    ADSR::Parameters envelopeParameters;
};

