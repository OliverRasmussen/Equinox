/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    Reverb.cpp
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

bool ReverbFX::isActive() const
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
    if (isActive())
    {
        dsp::AudioBlock<float> inputBlock (bufferToProcess);
        reverb.process(dsp::ProcessContextReplacing<float> (inputBlock));
    }
}
