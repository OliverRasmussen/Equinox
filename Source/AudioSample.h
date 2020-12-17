/*
  ==============================================================================

    AudioSample.h
    Created: 8 Dec 2020 3:59:05pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
// Format used for storing an audio sample with attributes
struct AudioSample
{
    String sampleName;
    String sampleFormat;
    int samplerate;
    int bitsPerSample;
    int numberOfChannels;
    int lengthInSamples;
    AudioBuffer<float> sampleSource;
    
    AudioSample(String sampleName,
                String sampleFormat,
                int samplerate,
                int bitsPerSample,
                int numberOfChannels,
                int lengthInSamples,
                AudioBuffer<float> sampleSource)
                : sampleName(sampleName),
                  sampleFormat(sampleFormat),
                  samplerate(samplerate),
                  bitsPerSample(bitsPerSample),
                  numberOfChannels(numberOfChannels),
                  lengthInSamples(lengthInSamples),
                  sampleSource(sampleSource)
    {
    }
};
