/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    AmpEnvelope.cpp
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
    envelopeParameters.attack = jmax(*attack, minAttackValue);
    envelopeParameters.decay = *decay;
    envelopeParameters.sustain = *sustain;
    envelopeParameters.release = jmax(*release, minReleaseValue);
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
