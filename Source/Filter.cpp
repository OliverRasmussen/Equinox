/*
  ==============================================================================

    Filter.cpp
    Created: 15 Apr 2020 9:44:46pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "Filter.h"

void Filter::prepareToPlay(dsp::ProcessSpec& spec)
{
    ladderFilter.prepare(spec);
    sampleRate = spec.sampleRate;
}

void Filter::reset()
{
    ladderFilter.reset();
}

void Filter::setMode(float* mode)
{
    int newMode = *mode;
    if(filterMode != newMode)
    {
        filterMode = newMode;
        switch (filterMode)
        {
            case 0:
                ladderFilter.setMode(dsp::LadderFilter<float>::Mode::LPF12);
                break;
            case 1:
                ladderFilter.setMode(dsp::LadderFilter<float>::Mode::HPF12);
                break;
            case 2:
                ladderFilter.setMode(dsp::LadderFilter<float>::Mode::LPF24);
                break;
            case 3:
                ladderFilter.setMode(dsp::LadderFilter<float>::Mode::HPF24);
                break;
            default:
                ladderFilter.setMode(dsp::LadderFilter<float>::Mode::LPF12);
                break;
        }
    }
}

bool Filter::isActive()
{
    return (filterMode == 0 || filterMode == 2) ? currentCutoffValue < sampleRate / 2 : currentCutoffValue > 0;
}

void Filter::setFilter(float* cutoff, float* resonance, float* drive)
{
    setCutoff(*cutoff);
    ladderFilter.setResonance(*resonance);
    ladderFilter.setDrive(*drive);
}

void Filter::setCutoff(float cutoff)
{
    currentCutoffValue = cutoff;
    ladderFilter.setCutoffFrequencyHz(cutoff);
}

float Filter::getCutoffValue() const
{
    return currentCutoffValue;
}

void Filter::process(AudioBuffer<float>& bufferToProcess)
{
    if (isActive())
    {
        dsp::AudioBlock<float> block (bufferToProcess);
        ladderFilter.process(dsp::ProcessContextReplacing<float> (block));
    }
}
