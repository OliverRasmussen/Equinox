/*
  ==============================================================================

    SampleSynthSound.cpp
    Created: 3 May 2020 11:26:20pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#include "SampleSynthSound.h"

SampleSynthSound::SampleSynthSound (const String& soundName,
                                    AudioFormatReader& source,
                                    const BigInteger& notes,
                                    int midiNoteForNormalPitch,
                                    double maxSampleLengthSeconds, int currentSamplerate)
    : name (soundName),
      sourceSampleRate (source.sampleRate),
      midiNotes (notes),
      midiRootNote (midiNoteForNormalPitch)
{
    
    if (sourceSampleRate > 0 && source.lengthInSamples > 0)
    {
//        length = jmin ((int) source.lengthInSamples,
//                       (int) (maxSampleLengthSeconds * sourceSampleRate));
        
        length = (int)source.lengthInSamples;

        data.reset (new AudioBuffer<float> (jmin (2, (int) source.numChannels), length + 4));

        source.read (data.get(), 0, length + 4, 0, true, true);
        
        // Resamples sourcesample if it isnt the same as the current samplerate
        if (sourceSampleRate != currentSamplerate)
        {
            double speedRatio = sourceSampleRate / currentSamplerate;
            AudioBuffer<float> tempResampleBuffer(data->getNumChannels(), (int)((double)length / speedRatio));

            const float **inputs  = data->getArrayOfReadPointers();
            float **outputs = tempResampleBuffer.getArrayOfWritePointers();

            resamplerL.reset();
            resamplerR.reset();
            resamplerL.process(speedRatio, inputs[0], outputs[0], tempResampleBuffer.getNumSamples());
            resamplerR.process(speedRatio, inputs[1], outputs[1], tempResampleBuffer.getNumSamples());

            data->makeCopyOf(tempResampleBuffer);

            length = data->getNumSamples();
            sourceSampleRate = 44100;
        }
    }
}

SampleSynthSound::~SampleSynthSound()
{
    
}

bool SampleSynthSound::appliesToNote (int midiNoteNumber)
{
    return midiNotes[midiNoteNumber];
}

bool SampleSynthSound::appliesToChannel (int /*midiChannel*/)
{
    return true;
}
