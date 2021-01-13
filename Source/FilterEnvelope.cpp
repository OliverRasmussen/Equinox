/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    FilterEnvelope.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "FilterEnvelope.h"
FilterEnvelope::FilterEnvelope(Filter& _filter) : filter(_filter)
{
    currentState = idleState;
}

void FilterEnvelope::prepareToPlay(double sampleRate)
{
    this->sampleRate = sampleRate/2;
}
       
void FilterEnvelope::setEnvelope(float *attack, float *decay, float *sustain, float *release)
{
    this->attack = *attack;
    this->decay = *decay;
    this->sustain = *sustain;
    this->release = *release;
    initialCutoffValue = filter.getCutoffValue();
}

void FilterEnvelope::setCutoffLimit(float *cutoffLimit)
{
    this->cutoffLimit = *cutoffLimit;
}
       
void FilterEnvelope::noteOn()
{
    sustainHasBeenSet = false;
    lastReachedValue = 0;
    //initialCutoffValue = filter.getCutoffValue();
    nextCutoffValue = initialCutoffValue;
    cutoffPct = cutoffLimit / 100;
    currentState = attackState;
    active = (attack > 0 || decay > 0 || sustain > 0 || release > 0);
}
       
void FilterEnvelope::noteOff()
{
    currentState = releaseState;
}
       
bool FilterEnvelope::isActive() const
{
    return active;
}

void FilterEnvelope::calculateNextValue()
{
    if (active)
    {
        switch (currentState)
        {
            case attackState:
                calculateNextAttackValue();
                break;
            case decayState:
                calculateNextDecayValue();
                break;
            case sustainState:
                calculateNextSustainValue();
                break;
            case releaseState:
                calculateNextReleaseValue();
                break;
            case idleState:
                active = false;
                break;
        }
    }
}

void FilterEnvelope::calculateNextAttackValue()
{
    float targetValue = cutoffLimit;
    
    if (attack == 0)
    {
        nextCutoffValue = targetValue;
        nextState();
        return;
    }
    
    float cutoffRate = (targetValue - initialCutoffValue) / attack;
    
    nextCutoffValue += cutoffRate;
    
    if (nextCutoffValue > targetValue)
    {
        nextCutoffValue = targetValue;
    }
    
    filter.setCutoff(nextCutoffValue);
    lastReachedValue = nextCutoffValue;
    
    if (nextCutoffValue == targetValue)
    {
        nextState();
    }
    
}

void FilterEnvelope::calculateNextDecayValue()
{
    if (decay == 0)
    {
        nextState();
        return;
    }
    
    float targetValue = initialCutoffValue + (cutoffPct * sustain);
    float cutoffRate;
    
    if (sustain > 1)
    {
        cutoffRate = (targetValue - initialCutoffValue) / decay;
    }
    else
    {
        cutoffRate = (cutoffLimit - initialCutoffValue) / decay;
    }
    
    nextCutoffValue -= cutoffRate;
    
    if (nextCutoffValue < targetValue)
    {
        nextCutoffValue = targetValue;
    }
    
    filter.setCutoff(nextCutoffValue);
    lastReachedValue = nextCutoffValue;
    
    if (nextCutoffValue == targetValue)
    {
        nextState();
    }
}

void FilterEnvelope::calculateNextSustainValue()
{
    if (sustain < 1)
    {
        return;
    }
    
    if (!sustainHasBeenSet)
    {
        float targetValue = initialCutoffValue + (cutoffPct * sustain);

        if (targetValue > sampleRate)
        {
            targetValue = sampleRate;
        }
        nextCutoffValue = targetValue;
        lastReachedValue = nextCutoffValue;
        sustainHasBeenSet = true;
    }
    
    filter.setCutoff(nextCutoffValue);
}

void FilterEnvelope::calculateNextReleaseValue()
{
    if (release == 0 || lastReachedValue == 0)
    {
        nextState();
        return;
    }
    
    float targetValue = initialCutoffValue;
    
    float cutoffRate = (lastReachedValue - initialCutoffValue) / release;
    
    nextCutoffValue -= cutoffRate;
    
    if (nextCutoffValue < targetValue)
    {
        nextCutoffValue = targetValue;
    }
    
    filter.setCutoff(nextCutoffValue);
    
    if (nextCutoffValue == targetValue)
    {
        nextState();
    }
}

void FilterEnvelope::nextState()
{
    currentState = static_cast<state>(currentState + 1);
}
