/*
  ==============================================================================

    FilterEnvelope.h
    Created: 18 Apr 2020 3:32:00am
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "ADSREnvelope.h"
#include "Filter.h"

class FilterEnvelope : public ADSREnvelope
{
public:
    
    FilterEnvelope (Filter&);

    void prepareToPlay (double sampleRate) override;
           
    void setEnvelope (float *attack, float *decay, float *sustain, float *release) override;
    
    void setCutoffLimit (float *cutoffLimit);
           
    void noteOn() override;
           
    void noteOff() override;
           
    bool isActive() const override;
    
    void setParameters() override;
    
private:
    
    Filter& filter;

    enum state {attackState, decayState, sustainState, releaseState, idleState};
    
    state currentState;
    
    void calculateNextAttackValue();
    
    void calculateNextDecayValue();
    
    void calculateNextSustainValue();
    
    void calculateNextReleaseValue();
    
    void nextState();
    
    float attack = 0, decay = 0, sustain = 0, release = 0;
    
    float cutoffLimit = 0;
    
    float initialCutoffValue = 0;
    
    float cutoffPct = 0;
    
    float nextCutoffValue = 0;
    
    float sampleRate = 0;
    
    float lastReachedValue = 0;
    
    bool enabled = false;
    
    bool active = false;
    
    bool notePlaying = false;
    
    bool sustainHasBeenSet = false;
};
