/*
  ==============================================================================

    SampleSynthSound.h
    Created: 3 May 2020 11:26:20pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include <JuceHeader.h>
#include "SampleSynthVoice.h"

class SampleSynthSound : public SynthesiserSound
{
    
public:
    
    SampleSynthSound(const String& sampleName, AudioBuffer<float>& source, int sourceSamplerate, int currentSamplerate);

    ~SampleSynthSound() override;
    
    const String& getName() const noexcept { return name; }
    
    AudioBuffer<float>* getAudioData() const noexcept { return data.get(); }

    bool appliesToNote(int midiNoteNumber) override;
    
    bool appliesToChannel(int midiChannel) override;

private:

    friend class SampleSynthVoice;
    
    String name;
    
    std::unique_ptr<AudioBuffer<float>> data;
    
    double sourceSamplerate;
    
    BigInteger midiNoteRange;
    
    int length = 0;
    int midiRootNote = 60; // center C
    
    CatmullRomInterpolator resamplerL;
    CatmullRomInterpolator resamplerR;
    
    void resampleSourceSamplerate(int currentSamplerate);
    
};

