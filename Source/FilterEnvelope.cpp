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
}

void FilterEnvelope::prepareToPlay(double sampleRate)
{
    envelope.setSampleRate(sampleRate);
}
       
void FilterEnvelope::setEnvelope(float *attack, float *decay, float *sustain, float *release)
{
    envelopeParameters.attack = *attack;
    envelopeParameters.decay = *decay;
    envelopeParameters.sustain = *sustain;
    envelopeParameters.release = *release;
    envelope.setParameters(envelopeParameters);

    if (!envelopeParameters.attack && 
        !envelopeParameters.decay && 
        !envelopeParameters.sustain && 
        !envelopeParameters.release)
    {
        envelope.reset();
        filter.modulateCutoff(filter.getCutoffValue());
        enabled = false;
    }
    else
    {
        enabled = true;
    }
}

void FilterEnvelope::setCutoffLimit(float *cutoffLimit)
{
    this->cutoffUpperLimit = *cutoffLimit;
}
       
void FilterEnvelope::noteOn()
{
    if (enabled)
    {
        cutoffLowerLimit = filter.getCutoffValue();
        filter.modulateCutoff(cutoffUpperLimit);
        envelope.noteOn();
    }
}
       
void FilterEnvelope::noteOff()
{
    if (enabled)
    {
        envelope.noteOff();
    }
}
       
bool FilterEnvelope::isActive() const
{
    return envelope.isActive() && enabled;
}

void FilterEnvelope::calculateNextValue()
{
    if (isActive())
    {
        float nextCutoffValue = ((cutoffUpperLimit - cutoffLowerLimit) * envelope.getNextSample()) + cutoffLowerLimit;
        filter.modulateCutoff(nextCutoffValue);
    }
}