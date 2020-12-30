/*
  ==============================================================================

    Chorus.cpp
    Created: 23 Dec 2020 10:37:29pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "ChorusFX.h"

ChorusFX::ChorusFX()
{
}

ChorusFX::~ChorusFX()
{
}

void ChorusFX::prepare(const dsp::ProcessSpec& spec)
{
    chorus.prepare(spec);
}

void ChorusFX::reset()
{
    chorus.reset();
}

bool ChorusFX::isActive()
{
    return mix > 0.0f;
}

void ChorusFX::setParameters(float rate, float depth, float delay, float feedback, float mix)
{
    if (mix == 0.0f)
    {
        reset();
    }
    
    chorus.setRate(rate);
    chorus.setDepth(depth);
    chorus.setCentreDelay(delay);
    chorus.setFeedback(feedback);
    this->mix = mix;
    chorus.setMix(mix);
}

void ChorusFX::process(AudioBuffer<float>& bufferToProcess)
{
    dsp::AudioBlock<float> inputBlock (bufferToProcess);
    chorus.process(dsp::ProcessContextReplacing<float> (inputBlock));
}
