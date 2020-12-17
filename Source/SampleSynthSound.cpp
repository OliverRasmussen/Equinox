/*
  ==============================================================================

    SampleSynthSound.cpp
    Created: 3 May 2020 11:26:20pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "SampleSynthSound.h"

SampleSynthSound::SampleSynthSound (AudioSample sample, int currentSamplerate)
{
    name = sample.sampleName;
    sourceSamplerate = sample.samplerate;
    midiNoteRange.setRange(0, 128, true);
    
    if (sourceSamplerate > 0 && sample.lengthInSamples > 0)
    {
        length = sample.lengthInSamples;
        
        data.reset (new AudioBuffer<float>(sample.sampleSource));
        
        if (sourceSamplerate != currentSamplerate)
        {
            resampleSourceSamplerate(currentSamplerate);
        }
    }
}

void SampleSynthSound::resampleSourceSamplerate(int currentSamplerate)
{
    double speedRatio = sourceSamplerate / currentSamplerate;
    AudioBuffer<float> tempResampleBuffer(data->getNumChannels(), (int)((double)length / speedRatio));

    const float **inputs  = data->getArrayOfReadPointers();
    float **outputs = tempResampleBuffer.getArrayOfWritePointers();

    resamplerL.reset();
    resamplerR.reset();
    resamplerL.process(speedRatio, inputs[0], outputs[0], tempResampleBuffer.getNumSamples());
    resamplerR.process(speedRatio, inputs[1], outputs[1], tempResampleBuffer.getNumSamples());

    data->makeCopyOf(tempResampleBuffer);

    length = data->getNumSamples();
    sourceSamplerate = currentSamplerate;
}

SampleSynthSound::~SampleSynthSound() {}

bool SampleSynthSound::appliesToNote (int midiNoteNumber)
{
    return midiNoteRange[midiNoteNumber];
}

bool SampleSynthSound::appliesToChannel (int /*midiChannel*/)
{
    return true;
}
