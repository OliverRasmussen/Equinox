/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    FilterEnvelope.h
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
    
    /** Prepares the filter envelope*/
    void prepareToPlay (double sampleRate) override;
    
    /** Sets the filter envelopes parameters*/
    void setEnvelope (float *attack, float *decay, float *sustain, float *release) override;
    
    /** Sets the cutoff limit*/
    void setCutoffLimit (float *cutoffLimit);
    
    /** Should be called when a note is triggered*/
    void noteOn() override;
    
    /** Should be called when a note is released*/
    void noteOff() override;
    
    /** Returns true if the filter envelope is currently active*/
    bool isActive() const override;
    
    /** Calculates the filter envelopes next value*/
    void calculateNextValue();
    
private:
    
    
    /** Calculates the next attack value*/
    void calculateNextAttackValue();
    
    /** Calculates the next decay value*/
    void calculateNextDecayValue();
    
    /** Calculates the next sustain value*/
    void calculateNextSustainValue();
    
    /** Calculates the next release value*/
    void calculateNextReleaseValue();
    
    /** Gets the next envelope state*/
    void nextState();
    
    Filter& filter;
    
    enum state {attackState, decayState, sustainState, releaseState, idleState};
    
    state currentState;
    
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
