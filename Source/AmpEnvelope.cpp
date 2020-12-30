/*
  ==============================================================================

    AmpEnvelope.cpp
    Created: 18 Apr 2020 3:31:42am
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "AmpEnvelope.h"

void AmpEnvelope::prepareToPlay(double sampleRate)
{
    envelope.setSampleRate(sampleRate);
}
       
void AmpEnvelope::setEnvelope(float *attack, float *decay, float *sustain, float *release)
{
    envelopeParameters.attack = *attack;
    envelopeParameters.decay = *decay;
    envelopeParameters.sustain = *sustain;
    envelopeParameters.release = *release;
    envelope.setParameters(envelopeParameters);
}
       
float AmpEnvelope::getNextSample()
{
    return envelope.getNextSample();
}

void AmpEnvelope::setSampleRate(double sampleRate)
{
    envelope.setSampleRate(sampleRate);
}
       
void AmpEnvelope::noteOn()
{
    envelope.noteOn();
}
       
void AmpEnvelope::noteOff()
{
    envelope.noteOff();
}
       
bool AmpEnvelope::isActive() const
{
    return envelope.isActive();
}
