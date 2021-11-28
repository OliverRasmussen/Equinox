/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    AudioSample.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
// Struct used for storing an audio sample with attributes
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
    ~AudioSample()
    {
    }
};
