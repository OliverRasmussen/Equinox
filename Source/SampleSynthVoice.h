/*
  ==============================================================================
     ______ ____   __  __ ____ _   __ ____  _  __
    / ____// __ \ / / / //  _// | / // __ \| |/ /
   / __/  / / / // / / / / / /  |/ // / / /|   /
  / /___ / /_/ // /_/ /_/ / / /|  // /_/ //   |
 /_____/ \___\_\\____//___//_/ |_/ \____//_/|_|
 
    SampleSynthVoice.h
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
    
    void prepareVoice(double sampleRate, int samplesPerBlock, int numChannels, dsp::ProcessSpec& spec) override;
    
    bool canPlaySound (SynthesiserSound*) override;
    
    void startNote (int midiNoteNumber, float velocity, SynthesiserSound* sound, int currentPitchWheelPosition) override;
    
    virtual void stopNote(float velocity, bool allowTailOff) override;
    
    float getNextSamplerSample (int channel, const float* const inL, const float* const inR);
    
    void renderNextBlock(AudioBuffer<float> &outputBuffer, int startSample, int numSamples) override;
    
private:
    
    double sourceSamplePositionLeft = 0;
    double sourceSamplePositionRight = 0;
    int sampleLength = 0;
    
    float gain = 10;

};
