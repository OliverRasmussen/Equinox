/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    Delay.cpp
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "DelayFX.h"

DelayFX::DelayFX() : delay(MAXIMUM_DELAY)
{
}

DelayFX::~DelayFX()
{
}

void DelayFX::prepare(const dsp::ProcessSpec& spec)
{
    samplerate = spec.sampleRate;
    
    delayBuffer = AudioBuffer<float> (spec.numChannels, spec.maximumBlockSize);
    
    delay.prepare(spec);
}

void DelayFX::reset()
{
    delay.reset();
}

bool DelayFX::isActive()
{
    return mix > 0.0f;
}

void DelayFX::setParameters(float time, float feedback, float mix)
{
    if (mix == 0.0f)
    {
        reset();
    }
    
    this->time = time;
    this->feedback = feedback * 0.01;
    this->mix = mix;
    delay.setDelay(calculateDelayInSamples());
}

float DelayFX::calculateDelayInSamples()
{
    float quarterNoteInSeconds = (MINUTE_IN_SECONDS / currentBPM) / 4;
    float delayInSeconds = quarterNoteInSeconds * time;
    float delayInSamples = delayInSeconds * samplerate;
    
    return delayInSamples;
}

void DelayFX::process(AudioBuffer<float>& bufferToProcess, double& bpm)
{
    
    // Checking if the currentBPM has changed
    if (currentBPM != bpm)
    {
        // Setting the current bpm and calculating the delay
        currentBPM = bpm;
        delay.setDelay(calculateDelayInSamples());
    }
    
    for (int sample = 0; sample < bufferToProcess.getNumSamples(); ++sample)
    {
        for (int channel = 0; channel < bufferToProcess.getNumChannels(); ++channel)
        {
            float delayedSample = delay.popSample(channel);
            
            // Adding the delayed sample to the buffer
            bufferToProcess.addSample(channel, sample, delayedSample * mix * feedback);
            
            float nextSample = bufferToProcess.getSample(channel, sample);
            
            // Pushing the next buffer sample to the delay
            delay.pushSample(channel, nextSample);
        }
    }
}
