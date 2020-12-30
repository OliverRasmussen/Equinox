/*
  ==============================================================================

    Reverb.cpp
    Created: 23 Dec 2020 10:37:21pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "ReverbFX.h"

ReverbFX::ReverbFX()
{
}

ReverbFX::~ReverbFX()
{
}

void ReverbFX::prepare(const dsp::ProcessSpec& spec)
{
    reverb.prepare(spec);
}

void ReverbFX::reset()
{
    reverb.reset();
}

bool ReverbFX::isActive()
{
    return reverbParameters.wetLevel > 0.0f;
}

void ReverbFX::setParameters(float roomSize, float damping, float width, float mix)
{
    if (mix == 0.0f)
    {
        reset();
    }
    
    reverbParameters.roomSize = roomSize;
    reverbParameters.damping = damping;
    reverbParameters.width = width;
    reverbParameters.dryLevel = 1.0f - mix;
    reverbParameters.wetLevel = mix;
    reverbParameters.freezeMode = 0.0f;
    
    reverb.setParameters(reverbParameters);
}

void ReverbFX::process(AudioBuffer<float>& bufferToProcess)
{
    dsp::AudioBlock<float> inputBlock (bufferToProcess);
    reverb.process(dsp::ProcessContextReplacing<float> (inputBlock));
}
