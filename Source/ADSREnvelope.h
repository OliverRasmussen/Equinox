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
    
    /** Prepares the envelope*/
    virtual void prepareToPlay(double sampleRate) = 0;
    
    /** Sets the envelope*/
    virtual void setEnvelope(float *attack, float *decay, float *sustain, float *release) = 0;
    
    /** Should be called when a note is triggered*/
    virtual void noteOn() = 0;
    
    /** Should be called when a note is released*/
    virtual void noteOff() = 0;
    
    /** Returns true if the envelope is active*/
    virtual bool isActive() const = 0;

protected:

    ADSR envelope;
    ADSR::Parameters envelopeParameters;
    
};
