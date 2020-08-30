/*
  ==============================================================================

    SampleSynthVoice.h
    Created: 1 May 2020 6:38:36pm
    Author:  Oliver Rasmussen

  ==============================================================================
*/

#pragma once
#include "SynthVoice.h"
#include "SampleSynthSound.h"

class SampleSynthVoice : public SynthVoice
{
    
public:
    
    SampleSynthVoice(bool isMonoVoice);
    
    ~SampleSynthVoice() override;
    
    bool canPlaySound (SynthesiserSound*) override;
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    virtual void stopNote(float velocity, bool allowTailOff) override;
    
    float getNextSamplerSample (int channel, const float* const inL, const float* const inR);
    
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
private:
    
    double sourceSamplePositionLeft = 0;
    double sourceSamplePositionRight = 0;
    double sourceSamplePosition = 0; //Should be deprecated
    int sampleLength = 0;
    
    float gain = 10, lgain = 10, rgain = 10; // l + r should be deprecated

};
