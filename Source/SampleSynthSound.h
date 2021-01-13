/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SampleSynthSound.h
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SampleSynthVoice.h"
#include "AudioSample.h"

class SampleSynthSound : public SynthesiserSound
{
    
public:
    
    SampleSynthSound(AudioSample sample, int currentSamplerate);

    ~SampleSynthSound() override;
    
    /** Returns the name of the current AudioSample*/
    const String& getName() const noexcept { return name; }
    
    /** Returns the AudioSamples audio data as an AudioBuffer*/
    AudioBuffer<float>* getAudioData() const noexcept { return data.get(); }

    bool appliesToNote(int midiNoteNumber) override;
    
    bool appliesToChannel(int midiChannel) override;

private:
    
    /** Resamples the AudioSample  to match the current samplerate*/
    void resampleSourceSamplerate(int currentSamplerate);

    friend class SampleSynthVoice;
    
    String name;
    
    std::unique_ptr<AudioBuffer<float>> data;
    
    double sourceSamplerate;
    
    BigInteger midiNoteRange;
    
    int length = 0;
    int midiRootNote = 60; // center C
    
    CatmullRomInterpolator resamplerL;
    CatmullRomInterpolator resamplerR;
    
    
};

